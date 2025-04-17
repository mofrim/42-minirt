/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/17 10:47:03 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
void	parse_object(t_objtype type, t_tokenizer *tok, t_scene *sc,
			void *(*parse_func)(t_tokenizer *))
{
	t_objlst	*obj;

	obj = objlst_new(type, parse_func(tok));
	objlst_add_back(&sc->objects, obj);
}

/* Dispatch to the individual parsing functions. */
void	handle_objects(t_token tok, t_scene *scene, t_tokenizer *tokenizer)
{
	if (ft_strcmp(tok.u_value.str, "sp") == 0)
		parse_object(SPHERE, tokenizer, scene, (void *)parse_sphere);
	else if (ft_strcmp(tok.u_value.str, "L") == 0)
		parse_object(LIGHT, tokenizer, scene, (void *)parse_light);
	else if (ft_strcmp(tok.u_value.str, "pl") == 0)
		parse_object(PLANE, tokenizer, scene, (void *)parse_plane);
	else if (ft_strcmp(tok.u_value.str, "cy") == 0)
		parse_object(CYLINDER, tokenizer, scene, (void *)parse_cylinder);
	else if (ft_strcmp(tok.u_value.str, "tr") == 0)
		parse_object(TRIANGLE, tokenizer, scene, (void *)parse_triangle);
	else if (ft_strcmp(tok.u_value.str, "ci") == 0)
		parse_object(CIRCLE, tokenizer, scene, (void *)parse_circle);
}

void	handle_token_keyword(t_tokenizer *tokenizer, t_scene *scene, t_token *token)
{
	if (ft_strcmp(token->u_value.str, "A") == 0)
		scene->alight = parse_ambient_light(tokenizer);
	else if (ft_strcmp(token->u_value.str, "C") == 0)
		scene->cam = parse_camera(tokenizer);
	else if (tok_is_object(*token) == true)
		handle_objects(*token, scene, tokenizer);
	else
		ft_dprintf(STDERR_FILENO, "Error\nInvalid keyword in scene file\n");
}
