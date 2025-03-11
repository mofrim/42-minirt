/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:01:37 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/09 11:49:13 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	draw_sidebar_seperator(t_mrt);
static void	show_keys(t_mrt mrt, int *i);
static void	show_mapinfo(t_mrt mrt, int *i);
void	print_mapinfo(t_mrt mrt, const char *txt, int prop, int *i);
void	print_menu_text(t_mrt mrt, int x, int y, char *txt);
void	print_mapinfo_float(t_mrt mrt, const char *txt, double prop, int *i);

void show_sidebar(t_mrt mrt)
{
	int i;

	draw_sidebar_seperator(mrt);
	mlx_set_font(mrt.mlx, mrt.win, FONT_DEFAULT);
	mlx_string_put(mrt.mlx, mrt.win, 15, 20, rgb_to_int("00ff00"),
			"MiniRT");
	i = 2;
	show_keys(mrt, &i);
	i += 2;
	show_mapinfo(mrt, &i);
	i += 2;
	print_menu_text(mrt, 15, 20 + (++i) * 15, "-- Current Map Params --");
	i++;
	print_mapinfo(mrt, "subsample: ",mrt.scene->subsample, &i);
	print_mapinfo(mrt, "fov: ", rad2deg_int(mrt.scene->cam->fov), &i);
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
}

static void	show_mapinfo(t_mrt mrt, int *i)
{
	print_menu_text(mrt, 15, 20 + (++(*i)) * 15, "-- Map Info --");
	(*i)++;
	print_mapinfo(mrt, "canvas width: ", CANVAS_WIDTH, i);
	print_mapinfo(mrt, "canvas height: ", WINY, i);
}
