/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_handle_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/21 20:03:49 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	bool	tok_is_object(char *key);
static void		parse_object(t_objtype type, t_tokenizer *tok, t_scene *sc,
					void *(*parse_func)(t_tokenizer *));
static void		handle_objects(t_scene *scene, t_tokenizer *tokenizer,
					char *key);

/**
 * Main keyword handler function.
 *
 * Checks if the token passed as param is a valid identifier. Then dispatches to
 * the corresponding parsing function which then tries to parse the complete
 * line according to the expected structure.
 */
void	handle_token_keyword(t_scene *scene, t_tokenizer *tokenizer, char *key)
{
	if (ft_strcmp(key, "A") == 0)
		scene->alight = parse_ambient_light(tokenizer);
	else if (ft_strcmp(key, "C") == 0)
		scene->cam = parse_camera(tokenizer);
	else if (tok_is_object(key) == true)
		handle_objects(scene, tokenizer, key);
	else
		print_errmsg("invalid keyword in scene file");
}

/* Dispatch to the individual parsing functions for objects. */
void	handle_objects(t_scene *scene, t_tokenizer *tokenizer, char *key)
{
	if (ft_strcmp(key, "sp") == 0)
		parse_object(SPHERE, tokenizer, scene, (void *)parse_sphere);
	else if (ft_strcmp(key, "L") == 0)
		parse_object(LIGHT, tokenizer, scene, (void *)parse_light);
	else if (ft_strcmp(key, "pl") == 0)
		parse_object(PLANE, tokenizer, scene, (void *)parse_plane);
	else if (ft_strcmp(key, "cy") == 0)
		parse_object(CYLINDER, tokenizer, scene, (void *)parse_cylinder);
	else if (ft_strcmp(key, "tr") == 0)
		parse_object(TRIANGLE, tokenizer, scene, (void *)parse_triangle);
	else if (ft_strcmp(key, "ci") == 0)
		parse_object(CIRCLE, tokenizer, scene, (void *)parse_circle);
}

/* Check if current identifier is for an object we know. */
static	bool	tok_is_object(char *key)
{
	if (ft_strlen(key) == 2 && (!ft_strcmp(key, "sp") || \
		!ft_strcmp(key, "cy") || !ft_strcmp(key, "pl") || \
		!ft_strcmp(key, "sp") || !ft_strcmp(key, "tr") || \
		!ft_strcmp(key, "ci")))
		return (true);
	else if (ft_strlen(key) == 1 && !ft_strcmp(key, "L"))
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
