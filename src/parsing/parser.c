/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/07 21:41:24 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parser	*parser_new(t_tokenizer *tokenizer)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	nullcheck(parser, "parser_new()");
	parser->tokenizer = tokenizer;
	return (parser);
}

void	parser_free(t_parser *parser)
{
	free(parser);
}

void	handle_token_keyword(t_parser *parser, t_scene *scene, t_token *token)
{
	t_objlst	*objlst;

	if (ft_strcmp(token->u_value.str, "A") == 0)
		scene->alight = parse_ambient_light(parser);
	else if (ft_strcmp(token->u_value.str, "C") == 0)
		scene->cam = parse_camera(parser);
	else if (ft_strcmp(token->u_value.str, "L") == 0)
	{
		objlst = objlst_new(LIGHT, parse_light(parser));
		objlst_add_back(&scene->objects, objlst);
	}
	else if (ft_strcmp(token->u_value.str, "sp") == 0)
	{
		objlst = objlst_new(SPHERE, parse_sphere(parser));
		objlst_add_back(&scene->objects, objlst);
	}
	else
		handle_more_keywords(parser, scene, token);
}

void	handle_more_keywords(t_parser *parser, t_scene *scene, t_token *token)
{
	t_objlst	*objlst;

	if (ft_strcmp(token->u_value.str, "pl") == 0)
	{
		objlst = objlst_new(PLANE, parse_plane(parser));
		objlst_add_back(&scene->objects, objlst);
	}
	else if (ft_strcmp(token->u_value.str, "cy") == 0)
	{
		objlst = objlst_new(CYLINDER, parse_cylinder(parser));
		objlst_add_back(&scene->objects, objlst);
	}
}
