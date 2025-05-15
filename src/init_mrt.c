/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:29:07 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/15 15:20:42 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		init_mlx_win(t_mrt *mrt);

t_mrt	*init_mrt(char *scene_filename)
{
	t_mrt	*mrt;

	mrt = malloc(sizeof(t_mrt));
	nullcheck(mrt, "Error\nmrt in init_mrt()");
	mrt->scene = parse_scene(scene_filename, mrt);
	init_mlx_win(mrt);
	setup_scene(*mrt);
	mrt->xc = init_xpm_canvas(mrt->mlx);
	nullcheck(mrt->xc, "Error\nxc in init_mrt()");
	mrt->autorep = false;
	mrt->last_key = 0;
	return (mrt);
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

/* Intialize scene struct. If malloc fails -> errorexit! Also setting subsample
 * to 10 here for a fluent first look at the scene. */
t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	nullcheck(scene, "init_scene()");
	scene->objects = NULL;
	scene->alight = NULL;
	scene->cam = NULL;
	scene->subsample = 10;
	scene->supersample = false;
	scene->samples_ppx = 4;
	scene->samples_ppx_half = 2;
	return (scene);
}
