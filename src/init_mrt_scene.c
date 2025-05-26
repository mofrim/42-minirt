/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mrt_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:29:07 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/26 20:31:00 by fmaurer          ###   ########.fr       */
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
	mrt->xc = init_xpm_canvas(mrt->mlx, CANVAS_WIDTH, WINY);
	mrt->sidebar = init_xpm_canvas(mrt->mlx, SIDEBAR_AREA_X - 40, WINY);
	nullcheck(mrt->xc, "Error\nxc in init_mrt()");
	mrt->autorep = false;
	mrt->last_key = 0;
	mrt->side_thm = set_sidethm_default();
	mrt->show_sidebar = true;
	mrt->can_params = (t_canvas_params){
		CANVAS_WIDTH, PIXEL_MINX, PIXEL_MAXX, PIXEL_MINY, PIXEL_MAXY,
		CANVAS_OFFSET_X, CANVAS_OFFSET_Y, SIDEBAR_AREA_X};
	mrt->rtfunc = RT_XPM;
	setup_scene(*mrt);
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
 * to 10 here for a fluent first look at the scene. The supersampling settings
 * are initalized to 4 and 2 which makes a good start. Another design decision:
 * if bump/normal mapping is wanted for any object, it will by done per default.
 * Can be deactivated later via 'B' key. */
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
	scene->sample_step = 1;
	scene->bump = true;
	scene->nmap = true;
	return (scene);
}
