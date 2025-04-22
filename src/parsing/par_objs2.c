/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_objs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/22 20:54:07 by fmaurer          ###   ########.fr       */
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

// FIXME: introduce TOKEN_TYPE_COLR in order to handle color parsing (i.e. with
// checking for correct value ranges and so on)
// t_colr	parse_color(t_parser *parser, bool *valid)
// {
// 	t_colr	color;
// 	t_token	*token;
// 	char	**parts;

// 	*valid = true;
// 	color.r = 255;
// 	color.g = 255;
// 	color.b = 255;
// 	token = tokenizer_next(parser->tokenizer);
// 	debug_token(token, "in parse_color");
// 	if (!token)
// 		return (color);
// 	if (token->type == TOKEN_TYPE_V3)
// 	{
// 		parts = ft_split(token->u_value.str, ',');
// 		if (parts && parts[0] && parts[1] && parts[2])
// 		{
// 			color.r = ft_atoi(parts[0]);
// 			color.g = ft_atoi(parts[1]);
// 			color.b = ft_atoi(parts[2]);
// 			free_parts(parts);
// 		}
// 	}
// 	token_free(token);
// 	return (validate_color(color, valid));
// }

// FIXME: idk its a little bit of a smell that colors are indistinguishable from
// TOKEN_TYPE_V3's. but for now it is okay i would say.
t_colr	parse_color(t_tokenizer *tok)
{
	t_colr	colr;
	t_token	*token;
	char	**parts;

	colr = (t_colr){0, 0, 0, 0};
	token = get_next_token(tok);
	if (!token || token->type != TOKEN_TYPE_V3)
	{
		if (token)
			token_free(token);
		print_errmsg("expected color format r,g,b");
		tok->valid = false;
		return (colr);
	}
	parts = ft_split(token->u_value.str, ',');
	if (!validate_color(parts, &tok->valid))
	{
		ft_freesplit(&parts);
		token_free(token);
		return (colr);
	}
	colr = (t_colr){ft_atoi(parts[0]), ft_atoi(parts[1]), ft_atoi(parts[2]), 0};
	ft_freesplit(&parts);
	token_free(token);
	return (colr);
}
