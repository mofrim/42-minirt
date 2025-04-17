/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:06:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/17 10:47:55 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*parse_light(t_tokenizer *tokenizer)
{
	t_light	*light;
	t_token	*token;
	bool valid;

	valid = true;
	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->pos = parse_v3(tokenizer, &valid);
	token = tokenizer_next(tokenizer);
	// FIXME: this anti-logic in here...
	if (token && token->type == TOKEN_TYPE_KEYWORD)
		light->bright = ft_atof(token->u_value.str);
	else if (token && token->type == TOKEN_TYPE_NUMBER)
		light->bright = token->u_value.num;
	else
		light->bright = 0.7;
	if (token)
		token_free(token);
	light->colr = parse_color(tokenizer, &valid);
	// FIXME: this anti-logic in here...
	light->colr.i = light->bright;
	return (light);
}

// FIXME: too many lines. LOGIC!!!
t_sphere	*parse_sphere(t_tokenizer *tokenizer)
{
	t_sphere	*sphere;
	t_token		*token;
	double		diameter;
	bool 		valid;

	valid = true;
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = parse_v3(tokenizer, &valid);
	token = tokenizer_next(tokenizer);
	if (token && token->type == TOKEN_TYPE_KEYWORD)
	{
		diameter = ft_atof(token->u_value.str);
		sphere->r = diameter / 2.0;
	}
	else if (token && token->type == TOKEN_TYPE_NUMBER)
	{
		diameter = token->u_value.num;
		sphere->r = diameter / 2.0;
	}
	else
		sphere->r = 1.0;
	sphere->r_squared = sphere->r * sphere->r;
	if (token)
		token_free(token);
	sphere->colr = parse_color(tokenizer, &valid);
	return (sphere);
}
