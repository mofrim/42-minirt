/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:29:07 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/23 14:26:35 by jroseiro         ###   ########.fr       */
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
	mrt->std_text_colr = rgb_to_int(YELLOW_GREEN);
	mrt->rtfunc = RT_XPM;
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

/* Intialize scene struct. If malloc fails -> errorexit! 
 * Also setting subsample
 * to 10 here for a fluent first look at the scene. 
 * The supersampling settings
 * are initalized to 4 and 2 which makes a good start.
 * Another design decision: if bump/normal mapping 
 * is wanted for any object, it will by
 * done per default. Can be deactivated later via 'B' key. */
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
