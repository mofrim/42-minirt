/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:06:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/17 19:37:38 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*parse_light(t_tokenizer *tokenizer)
{
	t_light	*light;
	t_token	*token;
	bool	valid;

	valid = true;
	light = malloc(sizeof(t_light));
	nullcheck(light, "parse_light()");
	light->pos = parse_v3(tokenizer, &valid);
	token = tokenizer_next(tokenizer);
	if (token && token->type == TOKEN_TYPE_NUMBER)
		light->bright = token->u_value.num;
	if (token)
		token_free(token);
	light->colr = parse_color(tokenizer, &valid);
	light->colr.i = light->bright;
	return (light);
}

// FIXME: too many lines. LOGIC!!!
// WHAT TO DO WITH THE VALID FLAG VAR & PROPER ERROR HANDLING IN ALL THESE
// FUNCTIONS!?!?!?!
t_sphere	*parse_sphere(t_tokenizer *tokenizer)
{
	t_sphere	*sphere;
	t_token		*token;
	bool 		valid;

	valid = true;
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = parse_v3(tokenizer, &valid);
	token = tokenizer_next(tokenizer);
	if (token && token->type == TOKEN_TYPE_NUMBER)
		sphere->r = token->u_value.num / 2.0;
	else
		return (NULL);
	sphere->r_squared = sphere->r * sphere->r;
	if (token)
		token_free(token);
	sphere->colr = parse_color(tokenizer, &valid);
	return (sphere);
}
