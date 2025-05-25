/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_objs_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:06:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/05/25 23:11:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	do_hyper_calculations(t_hyper *hyp);

/**
 * Parse a sphere.
 *
 * Expected Structure:
 * - center (t_v3)
 * - radius (float)
 * - color (t_colr)
 * (- specular (float) maybe...)
 * (- bump (float: bumpiness) tex tex_file_path)
 * (- tex tex_file_path)
 * (- nmap nmap_file_path)
 * (- tex tex_file_path nmap nmap_file_path)
 * (- bump tex tex_file_path nmap nmap_file_path)
 *
 * Example: "sp 0,0,0 10 255,0,0"
 * Rules: r > 0
 */
t_sphere	*parse_sphere(t_tokenizer *tok)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->tex_img = NULL;
	sphere->nmap_img = NULL;
	sphere->center = parse_v3(tok);
	sphere->r = parse_pos_num(tok) / 2.0;
	sphere->r_squared = sphere->r * sphere->r;
	sphere->colr = parse_color(tok);
	sphere->spec = parse_pos_num_maybe(tok);
	sphere->checker = parse_checker_maybe(tok);
	if (sphere->checker)
		sphere->checker_scale = parse_pos_num(tok);
	sphere->bump = parse_bump_maybe(tok);
	if (sphere->bump)
		sphere->bumpiness = parse_pos_num(tok);
	sphere->tex_file = parse_texture_maybe(tok);
	sphere->nmap_file = parse_nmap_maybe(tok);
	if (sphere->r <= 0)
		printerr_set_invalid("sphere radius has to be > 0", &tok->valid);
	return (sphere);
}

/**
 * Parse a cylinder.
 *
 * Expected Structure:
 * - center (t_v3)
 * - axis (t_v3)
 * - radius (t_colr)
 * - height (float)
 * - colr (t_colr)
 * (- spec (float))
 *
 * Example: "cy 0,0,0 0,1,0 2 10 0,255,0"
 * Rules: |axis| > 0
 */
t_cylinder	*parse_cylinder(t_tokenizer *tok)
{
	t_cylinder	*cyl;
	t_v3		half_h_vec;

	cyl = malloc(sizeof(t_cylinder));
	if (!cyl)
		return (NULL);
	cyl->center = parse_v3(tok);
	cyl->axis = parse_v3(tok);
	cyl->r = parse_pos_num(tok);
	cyl->height = parse_pos_num(tok);
	cyl->colr = parse_color(tok);
	cyl->spec = parse_pos_num_maybe(tok);
	cyl->axis = v3_normalize(cyl->axis);
	half_h_vec = v3_mult(cyl->axis, cyl->height / 2.0);
	cyl->p1 = v3_minus_v3(cyl->center, half_h_vec);
	cyl->p2 = v3_add_v3(cyl->center, half_h_vec);
	cyl->r_squared = cyl->r * cyl->r;
	if (v3_norm(cyl->axis) == 0)
		printerr_set_invalid("cylinder axis norm == 0", &tok->valid);
	if (cyl->r <= 0)
		printerr_set_invalid("cylinder radius <= 0", &tok->valid);
	if (cyl->height <= 0)
		printerr_set_invalid("cylinder height <= 0", &tok->valid);
	return (cyl);
}

/**
 * Parse a hyperboloid.
 *
 * Expected Structure:
 * - center (t_v3)
 * - axis (t_v3)
 * - ab (float)
 * - c (float)
 * - h (float)
 * - colr (t_colr)
 *
 * Example: "hy 0,0,0 0,1,0 2 4 10 0,255,0"
 * Rules: |axis|, ab, c, h > 0
 */
t_hyper	*parse_hyper(t_tokenizer *tok)
{
	t_hyper	*hyp;

	hyp = malloc(sizeof(t_hyper));
	nullcheck(hyp, "parse_hyper()");
	hyp->center = parse_v3(tok);
	hyp->axis = parse_v3(tok);
	hyp->ab = parse_pos_num(tok);
	hyp->c = parse_pos_num(tok);
	hyp->h = parse_pos_num(tok);
	hyp->colr = parse_color(tok);
	hyp->spec = parse_pos_num_maybe(tok);
	hyp->checker = parse_hyperchecker_maybe(tok);
	if (hyp->checker)
		hyp->checker_scale = parse_pos_num(tok);
	hyp->tex_file = parse_texture_maybe(tok);
	if (v3_norm(hyp->axis) == 0)
		printerr_set_invalid("hyperboloid axis norm == 0", &tok->valid);
	if (hyp->ab <= 0 || hyp->c <= 0 || hyp->h <= 0)
		printerr_set_invalid("hyperboloid ab, c or h == 0", &tok->valid);
	do_hyper_calculations(hyp);
	return (hyp);
}

void	do_hyper_calculations(t_hyper *hyp)
{
	hyp->axis = v3_normalize(hyp->axis);
	hyp->rcaps = hyp->ab * sqrt(1 + hyp->h * hyp->h / (4 * hyp->c * hyp->c));
	hyp->hym = hyper_get_rotmtrx(hyp->axis, hyp->ab, hyp->c);
	hyp->hby2 = hyp->h / 2;
	hyp->cap1.center = v3_add_v3(hyp->center, v3_mult(hyp->axis, hyp->hby2));
	hyp->cap1.r = hyp->rcaps;
	hyp->cap1.r2 = hyp->cap1.r * hyp->cap1.r;
	hyp->cap1.normal = hyp->axis;
	hyp->cap1.cdotn = v3_dot(hyp->cap1.normal, hyp->cap1.center);
	hyp->cap2.center = v3_minus_v3(hyp->center, v3_mult(hyp->axis, hyp->hby2));
	hyp->cap2.r = hyp->cap1.r;
	hyp->cap2.r2 = hyp->cap1.r2;
	hyp->cap2.normal = v3_mult(hyp->axis, -1);
	hyp->cap2.cdotn = v3_dot(hyp->cap2.normal, hyp->cap2.center);
}
