/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_objs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/23 00:51:25 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*parse_plane(t_tokenizer *tokenizer)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->pop = parse_v3(tokenizer);
	plane->normal = parse_v3(tokenizer);
	plane->colr = parse_color(tokenizer);
	return (plane);
}

t_cylinder	*parse_cylinder(t_tokenizer *tokenizer)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->center = parse_v3(tokenizer);
	cylinder->axis = parse_v3(tokenizer);
	cylinder->radius = parse_pos_num(tokenizer);
	cylinder->height = parse_pos_num(tokenizer);
	cylinder->colr = parse_color(tokenizer);
	return (cylinder);
}

// FIXME: should we do the calculations in here? have a `setup` function for
// every object?
t_triangle	*parse_triangle(t_tokenizer *tokenizer)
{
	t_triangle	*tr;

	tr = malloc(sizeof(t_triangle));
	nullcheck(tr, "Error\nparse_circle()");
	tr->a = parse_v3(tokenizer);
	tr->b = parse_v3(tokenizer);
	tr->c = parse_v3(tokenizer);
	tr->colr = parse_color(tokenizer);

	// FIXME calculations / setup
	tr->ab = v3_minus_vec(tr->b, tr->a);
	tr->ac = v3_minus_vec(tr->c, tr->a);
	tr->bc = v3_minus_vec(tr->c, tr->b);
	tr->normal = v3_mult(v3_cross(tr->ab, tr->ac), -1); // FIXME eeehmm
	tr->potdn = v3_dot(tr->a, tr->normal);
	tr->area = 0.5 * v3_norm(v3_cross(tr->ab, tr->ac));

	return (tr);
}

t_circle	*parse_circle(t_tokenizer *tokenizer)
{
	t_circle	*ci;

	ci = malloc(sizeof(t_circle));
	nullcheck(ci, "Error\nparse_circle()");
	ci->center = parse_v3(tokenizer);
	ci->normal = parse_v3(tokenizer);
	ci->r = parse_pos_num(tokenizer);
	ci->colr = parse_color(tokenizer);

	// FIXME calculations / setup
	ci->r2 = ci->r * ci->r;
	ci->normal = v3_get_norm(ci->normal);
	return (ci);
}
