/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:01:37 by fmaurer           #+#    #+#             */
/*   Updated: 2025/08/17 00:16:03 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ui.h"

static void	draw_sidebar_seperator(t_mrt mrt);
static void	show_keys(t_mrt mrt, int *i);
static void	show_mapinfo(t_mrt mrt, int *i);
static void	show_mapparams(t_mrt mrt, int *i);
void		print_mapinfo(t_mrt mrt, const char *txt, int prop, int *i);
void		print_menu_text(t_mrt mrt, int x, int y, char *txt);
void		print_mapinfo_float(t_mrt mrt, const char *txt, double prop,
				int *i);
void		print_mapinfo_bool(t_mrt mrt, const char *txt, bool prop, int *i);
void		print_menu_header(t_mrt mrt, int x, int y, char *txt);
void		print_rtfunc(t_mrt mrt, int *i);

/**
 * The sidebar.
 *
 * What a feature!!!
 */
void	show_sidebar(t_mrt mrt, bool draw_sep)
{
	int	i;

	if (draw_sep)
		draw_sidebar_seperator(mrt);
	mlx_string_put(mrt.mlx, mrt.win, 30, 20, mrt.side_thm.title_colr,
		"Jose's & Mofrim's miniRT");
	i = 2;
	show_keys(mrt, &i);
	i += 1;
	show_mapinfo(mrt, &i);
	i += 1;
	show_mapparams(mrt, &i);
}

static void	draw_sidebar_seperator(t_mrt mrt)
{
	int	i;

	i = -1;
	while (++i < WINY)
	{
		put_pixel_win(mrt, (t_pxl){SIDEBAR_AREA_X - 1, i},
			mrt.side_thm.sep_colr);
		put_pixel_win(mrt, (t_pxl){SIDEBAR_AREA_X - 2, i},
			mrt.side_thm.sep_colr);
	}
}

static void	show_keys(t_mrt mrt, int *i)
{
	print_menu_header(mrt, 30, 20 + (++(*i)) * 15, "-- shortcuts --");
	(*i)++;
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "esc = quit");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "],[  = +/- subsample");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "9,0  = +/- fov");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "-,=  = +/- abright");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "o  = export ppm");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "p  = print scene");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "w,a,s,d,e,q  = rot cam");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "->  = move cam");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "z,x,c,v  = choose rtfunc");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "b/n  = toggle bump/nmap");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "1,2  = subsample 1/10");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "3,4  = +/- supers. ppx");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "5,6  = +/- supers. step");
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "/ = toggle sidebar");
}

static void	show_mapinfo(t_mrt mrt, int *i)
{
	print_menu_header(mrt, 30, 20 + (++(*i)) * 15, "-- map info --");
	(*i)++;
	print_mapinfo(mrt, "canvas width: ", mrt.can_params.canvas_width, i);
	print_mapinfo(mrt, "canvas height: ", WINY, i);
	(*i)++;
	print_menu_header(mrt, 30, 20 + (++(*i)) * 15, "-- cam params --");
	(*i)++;
	if (mrt.scene->cam)
	{
		print_mapinfo(mrt, "fov: ", rad2deg_int(mrt.scene->cam->fov), i);
		print_mapinfo_float(mrt, "cam_pos.x : ", mrt.scene->cam->pos.x, i);
		print_mapinfo_float(mrt, "cam_pos.y : ", mrt.scene->cam->pos.y, i);
		print_mapinfo_float(mrt, "cam_pos.z : ", mrt.scene->cam->pos.z, i);
		print_mapinfo_float(mrt, "cam_orient.x: ", mrt.scene->cam->orient.x, i);
		print_mapinfo_float(mrt, "cam_orient.y: ", mrt.scene->cam->orient.y, i);
		print_mapinfo_float(mrt, "cam_orient.z: ", mrt.scene->cam->orient.z, i);
	}
}

static void	show_mapparams(t_mrt mrt, int *i)
{
	print_menu_header(mrt, 30, 20 + (++(*i)) * 15,
		"-- current scene params --");
	(*i)++;
	if (mrt.scene->alight)
		print_mapinfo_float(mrt, "abright: ", mrt.scene->alight->i, i);
	print_mapinfo(mrt, "subsample: ", mrt.scene->subsample, i);
	print_mapinfo_bool(mrt, "supersample: ", mrt.scene->supersample, i);
	if (mrt.scene->supersample)
	{
		print_mapinfo(mrt, "  ppx: ", mrt.scene->samples_ppx, i);
		print_mapinfo(mrt, "  step: ", mrt.scene->sample_step, i);
	}
	print_mapinfo_bool(mrt, "nmapping: ", mrt.scene->nmap, i);
	print_mapinfo_bool(mrt, "bumpmapping: ", mrt.scene->bump, i);
	print_rtfunc(mrt, i);
}
