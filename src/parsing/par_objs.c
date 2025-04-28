/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:06:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/28 22:25:09 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*parse_light(t_tokenizer *tok)
{
	t_light	*light;
	float	bright;

	light = malloc(sizeof(t_light));
	nullcheck(light, "parse_light()");
	light->pos = parse_v3(tok);
	bright = parse_pos_num(tok);
	if (bright > 1.0)
		printerr_set_invalid("pointlight too bright", &tok->valid);
	light->colr = parse_color(tok);
	light->colr.i = bright;
	return (light);
}

/**
 * Parse a sphere.
 *
 * Structure:
 * - center (t_v3)
 * - radius (float)
 * - color (t_colr)
 */
t_sphere	*parse_sphere(t_tokenizer *tokenizer)
{
	t_sphere	*sphere;
	t_token		*token;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = parse_v3(tokenizer);
	token = get_next_token(tokenizer);
	if (token && token->type == TOKEN_TYPE_NUM)
		sphere->r = token->u_value.num / 2.0;
	else
		return (NULL);
	sphere->r_squared = sphere->r * sphere->r;
	if (token)
		token_free(&token);
	sphere->colr = parse_color(tokenizer);
	return (sphere);
}
