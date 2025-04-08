/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/08 10:41:02 by fmaurer          ###   ########.fr       */
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

/* Check if current identifier is for an object we know. */
// QUESTION: what happens if there is an unknown object???
static	bool	tok_is_object(t_token tok)
{
	char	*str;

	str = tok.u_value.str;
	if (!ft_strcmp(str, "sp") || !ft_strcmp(str, "cy") || \
		!ft_strcmp(str, "pl") || !ft_strcmp(str, "sp") || \
		!ft_strcmp(str, "tr") || !ft_strcmp(str, "ci") || \
		!ft_strcmp(str, "L"))
		return (true);
	return (false);
}

/* Generic function for adding a new object to the scenes objlst. */
void	parse_object(t_objtype type, t_parser *par, t_scene *sc,
			void *(*parse_func)(t_parser *))
{
	t_objlst	*obj;

	obj = objlst_new(type, parse_func(par));
	objlst_add_back(&sc->objects, obj);
}

/* Dispatch to the individual parsing functions. */
void	handle_objects(t_token tok, t_scene *scene, t_parser *parser)
{
	if (ft_strcmp(tok.u_value.str, "sp") == 0)
		parse_object(SPHERE, parser, scene, (void *)parse_sphere);
	else if (ft_strcmp(tok.u_value.str, "L") == 0)
		parse_object(LIGHT, parser, scene, (void *)parse_light);
	else if (ft_strcmp(tok.u_value.str, "pl") == 0)
		parse_object(PLANE, parser, scene, (void *)parse_plane);
	else if (ft_strcmp(tok.u_value.str, "cy") == 0)
		parse_object(CYLINDER, parser, scene, (void *)parse_cylinder);
	else if (ft_strcmp(tok.u_value.str, "tr") == 0)
		parse_object(TRIANGLE, parser, scene, (void *)parse_triangle);
	else if (ft_strcmp(tok.u_value.str, "ci") == 0)
		parse_object(CIRCLE, parser, scene, (void *)parse_circle);
}

void	handle_token_keyword(t_parser *parser, t_scene *scene, t_token *token)
{
	if (ft_strcmp(token->u_value.str, "A") == 0)
		scene->alight = parse_ambient_light(parser);
	else if (ft_strcmp(token->u_value.str, "C") == 0)
		scene->cam = parse_camera(parser);
	else if (tok_is_object(*token) == true)
		handle_objects(*token, scene, parser);
	else
		ft_dprintf(STDERR_FILENO, "Error\nInvalid keyword in scene file\n");
}
