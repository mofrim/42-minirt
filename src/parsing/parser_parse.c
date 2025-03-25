/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:05:30 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/07 21:41:51 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_scene	*parser_parse(t_parser *parser)
{
	t_scene	*scene;
	bool	valid;

	valid = true;
	scene = init_scene();
	if (!scene)
		return (NULL);
	parse_tokens_recursive(parser, scene, &valid);
	if (!valid)
		return (NULL);
	return (scene);
}

void	token_free(t_token *token)
{
	if (token)
	{
		if (token->type == TOKEN_TYPE_KEYWORD || \
			token->type == TOKEN_TYPE_IDENTIFIER || \
			token->type == TOKEN_TYPE_SYMBOL)
		{
			free(token->u_value.str);
		}
		free(token);
	}
}

t_amb_light	*parse_ambient_light(t_parser *parser)
{
	t_amb_light	*amb_light;
	bool valid;

	valid = true;
	amb_light = malloc(sizeof(t_amb_light));
	nullcheck(amb_light, "parse_ambient_light()");
	skip_whitespace(parser->tokenizer);
	amb_light->bright = parse_number(parser->tokenizer);
	amb_light->colr = parse_color(parser, &valid);
	return (amb_light);
}

t_camera	*parse_camera(t_parser *parser)
{
	t_camera	*camera;
	t_token		*token;
	bool valid;

	valid = true;
	camera = malloc(sizeof(t_camera));
	nullcheck(camera, "parse_camera");
	camera->pos = parse_v3(parser, &valid);
	camera->orient = parse_v3(parser, &valid);
	token = tokenizer_next(parser->tokenizer);
	if (token && token->type == TOKEN_TYPE_NUMBER)
	{
		camera->fov = token->u_value.num;
		token_free(token);
	}
	else
	{
		camera->fov = 70.0;
		if (token)
			token_free(token);
	}
	return (camera);
}
