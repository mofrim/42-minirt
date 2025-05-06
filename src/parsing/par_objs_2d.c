/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_objs_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/05/06 20:48:25 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Parse a triangle.
 *
 * Expected Structure:
 * - corner a (t_v3)
 * - corner b (t_v3)
 * - corner c (t_v3)
 * - colr (t_colr)
 *
 * Example: "tr -1,0,0 0,1,0 0,0,1 0,255,0"
 * Rules: a != b != c <=> ab,ac,bc != 0
 *
 * b - a != 0 => b != a
 * c - a != 0 => c != a
 * c - b != 0 => b != c
 *
 */
t_triangle	*parse_triangle(t_tokenizer *tok)
{
	t_triangle	*tr;

	tr = malloc(sizeof(t_triangle));
	nullcheck(tr, "Error\nparse_triangle()");
	tr->a = parse_v3(tok);
	tr->b = parse_v3(tok);
	tr->c = parse_v3(tok);
	tr->colr = parse_color(tok);
	tr->spec = parse_pos_num_maybe(tok);
	tr->ab = v3_minus_vec(tr->b, tr->a);
	tr->ac = v3_minus_vec(tr->c, tr->a);
	tr->bc = v3_minus_vec(tr->c, tr->b);
	if (v3_norm(tr->ab) * v3_norm(tr->ac) * v3_norm(tr->bc) == 0)
		printerr_set_invalid("2 equal points in triangle def", &tok->valid);
	tr->normal = v3_normalize(v3_cross(tr->ab, tr->ac));
	tr->potdn = v3_dot(tr->a, tr->normal);
	tr->area = 0.5 * v3_norm(v3_cross(tr->ab, tr->ac));
	return (tr);
}

/**
 * Parse a circle.
 *
 * Expected Structure:
 * - circle center (t_v3)
 * - normal vector (t_v3)
 * - diameter(!) (float)
 * - colr (t_colr)
 *
 * Example: "ci 0,0,0 0,1,0 10 0,255,0"
 * Rules: |norm|, r > 0
 */
t_circle	*parse_circle(t_tokenizer *tok)
{
	t_circle	*ci;

	ci = malloc(sizeof(t_circle));
	nullcheck(ci, "Error\nparse_circle()");
	ci->center = parse_v3(tok);
	ci->normal = parse_v3(tok);
	ci->r = parse_pos_num(tok) / 2.0;
	ci->colr = parse_color(tok);
	ci->spec = parse_pos_num_maybe(tok);
	if (v3_norm(ci->normal) == 0)
		printerr_set_invalid("circle normal norm == 0", &tok->valid);
	if (ci->r == 0)
		printerr_set_invalid("circle diameter == 0", &tok->valid);
	ci->r2 = ci->r * ci->r;
	ci->normal = v3_normalize(ci->normal);
	return (ci);
}

/**
 * Parse a plane.
 *
 * Expected Structure:
 * - point on plane (t_v3)
 * - normal vector (t_v3)
 * - color (t_colr)
 *
 * Example: "pl 0,0,0 0,1,0 0,255,0"
 * Rules: |norm| > 0
 */
t_plane	*parse_plane(t_tokenizer *tok)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->pop = parse_v3(tok);
	plane->normal = parse_v3(tok);
	plane->colr = parse_color(tok);
	plane->spec = parse_pos_num_maybe(tok);
	if (v3_norm(plane->normal) == 0)
		printerr_set_invalid("plane normal norm == 0", &tok->valid);
	return (plane);
}
