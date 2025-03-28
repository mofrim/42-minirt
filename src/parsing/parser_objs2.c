/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/28 18:52:32 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*parse_plane(t_parser *parser)
{
	t_plane	*plane;
	bool valid;
	
	valid = true;
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->pop = parse_v3(parser, &valid);
	plane->normal = parse_v3(parser, &valid);
	plane->colr = parse_color(parser, &valid);
	return (plane);
}

t_cylinder	*parse_cylinder(t_parser *parser)
{
	t_cylinder	*cylinder;
	bool valid;

	valid = true;
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->center = parse_v3(parser, &valid);
	cylinder->axis = parse_v3(parser, &valid);
	cylinder->radius = parse_number(parser->tokenizer);
	cylinder->height = parse_number(parser->tokenizer);
	cylinder->colr = parse_color(parser, &valid);
	return (cylinder);
}

// FIXME: introduce TOKEN_TYPE_COLR in order to handle color parsing (i.e. with
// checking for correct value ranges and so on)
t_colr	parse_color(t_parser *parser, bool *valid)
{
	t_colr	color;
	t_token	*token;
	char	**parts;

	*valid = true;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	token = tokenizer_next(parser->tokenizer);
	debug_token(token, "in parse_color");
	if (!token)
		return (color);
	if (token->type == TOKEN_TYPE_V3)
	{
		parts = ft_split(token->u_value.str, ',');
		if (parts && parts[0] && parts[1] && parts[2])
		{
			color.r = ft_atoi(parts[0]);
			color.g = ft_atoi(parts[1]);
			color.b = ft_atoi(parts[2]);
			free_parts(parts);
		}
	}
	token_free(token);
	return (validate_color(color, valid));
}
