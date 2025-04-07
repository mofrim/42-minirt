/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:29:07 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/07 23:50:46 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		init_mlx_win(t_mrt *mrt);
static t_scene	*parse_scene(char *scene_filename);

t_mrt	*init_mrt(char *scene_filename)
{
	t_mrt	*mrt;

	mrt = malloc(sizeof(t_mrt));
	nullcheck(mrt, "Error\nmrt in init_mrt()");
	init_mlx_win(mrt);
	mrt->scene = parse_scene(scene_filename);
	mrt->xc = init_xpm_canvas(mrt->mlx);
	nullcheck(mrt->xc, "Error\nxc in init_mrt()");
	return (mrt);
}

t_scene	*parse_scene(char *scene_filename)
{
	t_scene		*scene;
	t_tokenizer	*tokenizer;
	t_parser	*parser;
	char		*content;

	content = validate_file_content(scene_filename);
	tokenizer = tokenizer_new(content);
	parser = parser_new(tokenizer);
	scene = parser_parse(parser);
	if (!scene)
	{
		free(content);
		tokenizer_free(tokenizer);
		parser_free(parser);
		exit_with_errmsg("Error\nFailed to parse scene");
	}
	tokenizer_free(tokenizer);
	parser_free(parser);
	free(content);
	debug_parsed_scene(scene);
	setup_scene(scene);
	return (scene);
}

static void	init_mlx_win(t_mrt *mrt)
{
	mrt->mlx = mlx_init();
	if (!mrt->mlx)
		exit_with_errmsg("Error\n!! mlx_init fail !!");
	mrt->win = mlx_new_window(mrt->mlx, WINX, WINY, "minirt");
	if (!mrt->win)
		exit_with_errmsg("Error\n!! mlx_new_window fail !!");
}
