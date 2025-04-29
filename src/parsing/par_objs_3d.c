/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:06:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/29 11:06:12 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Parse a sphere.
 *
 * Expected Structure:
 * - center (t_v3)
 * - radius (float)
 * - color (t_colr)
 *
 * Example: "sp 0,0,0 10 255,0,0"
 * Rulse: all checked by parsing funcs
 */
t_sphere	*parse_sphere(t_tokenizer *tok)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = parse_v3(tok);
	sphere->r = parse_pos_num(tok) / 2.0;
	sphere->r_squared = sphere->r * sphere->r;
	sphere->colr = parse_color(tok);
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
 *
 * Example: "cy 0,0,0 0,1,0 2 10 0,255,0"
 * Rules: |axis| > 0
 */
t_cylinder	*parse_cylinder(t_tokenizer *tok)
{
	t_cylinder	*cyl;

	cyl = malloc(sizeof(t_cylinder));
	if (!cyl)
		return (NULL);
	cyl->center = parse_v3(tok);
	cyl->axis = parse_v3(tok);
	if (v3_norm(cyl->axis) == 0)
		printerr_set_invalid("cylinder axis norm == 0", &tok->valid);
	cyl->radius = parse_pos_num(tok);
	cyl->height = parse_pos_num(tok);
	cyl->colr = parse_color(tok);
	return (cyl);
}
