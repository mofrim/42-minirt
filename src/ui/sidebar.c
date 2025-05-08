/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:01:37 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 10:08:15 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	draw_sidebar_seperator(t_mrt mrt);
static void	show_keys(t_mrt mrt, int *i);
static void	show_mapinfo(t_mrt mrt, int *i);
void		print_mapinfo(t_mrt mrt, const char *txt, int prop, int *i);
void		print_menu_text(t_mrt mrt, int x, int y, char *txt);
void		print_mapinfo_float(t_mrt mrt, const char *txt, double prop,
				int *i);

void	show_sidebar(t_mrt mrt)
{
	int	i;

	draw_sidebar_seperator(mrt);

	/* Sadly this just causes a lot memory garbage.. i think we should keep it
	 * umcommented for dev because it spoils the valgrind output. in the final
	 * version we can uncomment and explain that it is due to mlx issues.
	 *
	 * 		mlx_set_font(mrt.mlx, mrt.win, FONT_DEFAULT);
	 */

	mlx_string_put(mrt.mlx, mrt.win, 15, 20, rgb_to_int("00ff00"),
		"Jose's & Mofrim's miniRT");
	i = 2;
	show_keys(mrt, &i);
	i += 2;
	show_mapinfo(mrt, &i);
	i += 2;
	print_menu_text(mrt, 15, 20 + (++i) * 15, "-- current Map Params --");
	i++;
	print_mapinfo(mrt, "subsample: ", mrt.scene->subsample, &i);
	if (mrt.scene->alight)
		print_mapinfo_float(mrt, "abright: ", mrt.scene->alight->colr.i, &i);
}

static void	draw_sidebar_seperator(t_mrt mrt)
{
	int	i;

	i = -1;
	while (++i < WINY)
	{
		put_pixel_win(mrt, (t_pxl){SIDEBAR_AREA_X, i}, "00aa00");
		put_pixel_win(mrt, (t_pxl){SIDEBAR_AREA_X - 1, i}, "00aa00");
	}
}

static void	show_keys(t_mrt mrt, int *i)
{
	print_menu_text(mrt, 15, 20 + (++(*i)) * 15, "-- Shortcuts --");
	(*i)++;
	print_menu_text(mrt, 15, 20 + (++(*i)) * 15, "esc = quit");
	print_menu_text(mrt, 15, 20 + (++(*i)) * 15, "][  = +/- subsample");
	print_menu_text(mrt, 15, 20 + (++(*i)) * 15, ")(  = +/- fov");
	print_menu_text(mrt, 15, 20 + (++(*i)) * 15, "-/=  = +/- abright");
}

static void	show_mapinfo(t_mrt mrt, int *i)
{
	print_menu_text(mrt, 15, 20 + (++(*i)) * 15, "-- Map Info --");
	(*i)++;
	print_mapinfo(mrt, "canvas width: ", CANVAS_WIDTH, i);
	print_mapinfo(mrt, "canvas height: ", WINY, i);
	(*i)++;
	print_menu_text(mrt, 15, 20 + (++(*i)) * 15, "-- cam params --");
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
