/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_xpm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:23:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/30 13:31:01 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "xpm.h"

t_v3	canvas2viewport(int cx, int cy, t_camera cam);
t_colr	traceray(t_scene scene, t_v3 ray_dir);

/**
 * Raytracing function putting pixel to xpm in mem.
 *
 * Description: clear, isn't it? The idea here was the following: It should be
 * faster to first collect the raytraced-scene in mem and then put it to the
 * screen all at once, rather then calling mlx_put_pixel again and again.
 * Another idea was, with the scene in mem we could "easily" implement
 * functionality to save stuff to a file on disk.. done in `export_ppm()` :)
 */
void	raytrace_xpm(t_mrt mrt)
{
	int				cx;
	int				cy;
	t_v3			ray_dir;
	t_colr			px_colr;

	cx = PIXEL_MINX;
	px_colr = mrt.scene->alight->colr;
	while (cx < PIXEL_MAXX)
	{
		cy = PIXEL_MINY;
		while (cy < PIXEL_MAXY)
		{
			if (!(cy % mrt.scene->subsample) || cy == PIXEL_MINY || \
					cx == PIXEL_MINX)
			{
				ray_dir = canvas2viewport(cx, cy, *mrt.scene->cam);
				px_colr = traceray(*mrt.scene, ray_dir);
			}
			put_pixel_xpm(mrt.xc, cx, cy, px_colr);
			cy++;
		}
		cx++;
	}
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.xc->img, SIDEBAR_AREA_X, 0);
}
