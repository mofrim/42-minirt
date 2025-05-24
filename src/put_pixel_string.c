/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:18:17 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 18:15:12 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Put a pixel to the screen. The origin for xy-coords is the center of the
 * window. Only puts the pixels if pixel is still on canvas! The color is
 * specified using our t_colr type. */
void	put_pixel_canvas_rt(t_mrt mrt, t_pxl pos, t_colr pxlcolr)
{
	int				sx;
	int				sy;
	t_canvas_params	cp;

	cp = mrt.can_params;
	if (cp.pixel_minx < pos.x && pos.x < cp.pixel_maxx && \
cp.pixel_miny < pos.y && pos.y < cp.pixel_maxy)
	{
		sx = cp.canvas_offset_x + pos.x;
		sy = cp.canvas_offset_y - pos.y;
		mlx_pixel_put(mrt.mlx, mrt.win, sx, sy, tcolr_to_int(pxlcolr));
	}
}

/* Put a pixel to the window.. the coordinate system here has its origin in the
 * lower left corner of the window. */
void	put_pixel_win(t_mrt	mrt, t_pxl pos, int colr)
{
	int	sx;
	int	sy;

	sx = pos.x;
	sy = WINY - pos.y;
	mlx_pixel_put(mrt.mlx, mrt.win, sx, sy, colr);
}

/* Wrapper around the mlx string put function. Origin is OURs which is at the
 * center of the canvas. */
void	put_string_canvas(t_mrt mrt, t_pxl pos, char *colr, char *txt)
{
	int	sx;
	int	sy;

	sx = WINX / 2 + pos.x;
	sy = WINY / 2 - pos.y;
	mlx_string_put(mrt.mlx, mrt.win, sx, sy, rgb_to_int(colr), txt);
}
