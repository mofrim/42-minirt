/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_handle_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/05/08 09:48:21 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	tok_is_object(char *key);
static void	parse_object(t_objtype type, t_tokenizer *tok, t_scene *sc,
				void *(*parse_func)(t_tokenizer *));
static void	handle_objects(t_scene *scene, t_tokenizer *tokenizer,
				char *key);

/**
 * Main keyword handler function.
 *
 * Checks if the token passed as param is a valid identifier. Then dispatches to
 * the corresponding parsing function which then tries to parse the complete
 * line according to the expected structure.
 * NOTE: Because we always dispatch to the corresponding parsing functions for
 * each keyword the structure of each line is determined by each parsing func!
 * This means: the individual element-parsing functions like `parse__v3` or
 * `parse_colr` get called in the expected order. This means if any error is
 * encountered in a element-parsing func the scenefile is invalid.
 * This has implications for the error messaging: We can always say "vector was
 * expected" or "color was expected".
 */
void	handle_token_keyword(t_scene *scene, t_tokenizer *tok, char *key)
{
	if (ft_strcmp(key, "A") == 0)
	{
		if (scene->alight)
			printerr_set_invalid("already got one ambient light", &tok->valid);
		else
			scene->alight = parse_ambient_light(tok);
	}
	else if (ft_strcmp(key, "C") == 0)
	{
		if (scene->cam)
			printerr_set_invalid("already got one cam", &tok->valid);
		else
			scene->cam = parse_camera(tok);
	}
	else if (tok_is_object(key) == true)
		handle_objects(scene, tok, key);
	else
		print_errmsg("invalid keyword in scene file", key);
}

/* Dispatch to the individual parsing functions for objects. */
void	handle_objects(t_scene *scene, t_tokenizer *tok, char *key)
{
	if (ft_strcmp(key, "sp") == 0)
		parse_object(SPHERE, tok, scene, (void *)parse_sphere);
	else if (ft_strcmp(key, "L") == 0)
		parse_object(LIGHT, tok, scene, (void *)parse_light);
	else if (ft_strcmp(key, "pl") == 0)
		parse_object(PLANE, tok, scene, (void *)parse_plane);
	else if (ft_strcmp(key, "cy") == 0)
		parse_object(CYLINDER, tok, scene, (void *)parse_cylinder);
	else if (ft_strcmp(key, "tr") == 0)
		parse_object(TRIANGLE, tok, scene, (void *)parse_triangle);
	else if (ft_strcmp(key, "ci") == 0)
		parse_object(CIRCLE, tok, scene, (void *)parse_circle);
	else if (ft_strcmp(key, "hy") == 0)
		parse_object(HYPER, tok, scene, (void *)parse_hyper);
}

/* Check if current identifier is for an object we know. */
bool	tok_is_object(char *key)
{
	if (ft_strlen(key) == 2 && (!ft_strcmp(key, "sp") || \
!ft_strcmp(key, "cy") || !ft_strcmp(key, "pl") || \
!ft_strcmp(key, "sp") || !ft_strcmp(key, "tr") || \
!ft_strcmp(key, "ci") || !ft_strcmp(key, "hy")))
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
