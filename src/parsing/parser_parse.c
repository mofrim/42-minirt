/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:05:30 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/22 16:10:45 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_tokens_recursive(t_parser *parser, t_scene *scene)
{
	t_token	*token;
	
	token = tokenizer_next(parser->tokenizer);
	if (!token)
		return;
	
	if (token->type == TOKEN_TYPE_KEYWORD)
		handle_token_keyword(parser, scene, token);
	
	token_free(token);
	parse_tokens_recursive(parser, scene);
}

t_scene	*parser_parse(t_parser *parser)
{
	t_scene	*scene;
	
	scene = init_scene();
	if (!scene)
		return (NULL);
	
	parse_tokens_recursive(parser, scene);
	return (scene);
}

void	token_free(t_token *token)
{
	if (token)
	{
		if (token->type == TOKEN_TYPE_KEYWORD ||
			token->type == TOKEN_TYPE_IDENTIFIER ||
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

	amb_light = malloc(sizeof(t_amb_light));
	if (!amb_light)
		return (NULL);
	amb_light->bright = parse_number(parser->tokenizer);
	amb_light->colr = parse_color(parser);
	return (amb_light);
}

t_camera	*parse_camera(t_parser *parser)
{
	t_camera	*camera;
	t_token		*token;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->pos = parse_v3(parser);
	camera->orient = parse_v3(parser);

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
