/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui-utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:33:36 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/26 20:24:05 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_axis(t_mrt mrt)
{
	int		i;
	t_colr	c;

	c = (t_colr){42, 42, 42, 0.5};
	i = -1;
	while (++i < CANVAS_WIDTH)
	{
		put_pixel_canvas_rt(mrt, (t_pxl){i, 0}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){-i, 0}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){0, i}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){0, -i}, c);
	}
}

/* Put a black img over the sidebar area to clear it and then draw everything
 * again. Not the most efficient way to do it, but it works. */
void	update_sidebar(t_mrt *mrt)
{
	mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->sidebar->img,
		20, 0);
	show_sidebar(*mrt, false);
}

/* Redraw window content after changes to scene have been made. */
void	redraw_win(t_mrt *mrt, bool print_msg)
{
	if (mrt->show_sidebar)
		update_sidebar(mrt);
	if (print_msg || mrt->scene->subsample <= 6)
	{
		put_string_canvas(*mrt, (t_pxl){-50, 0}, GREEN, "tracing rays...");
		mlx_do_sync(mrt->mlx);
	}
	launch_raytrace(*mrt);
}
