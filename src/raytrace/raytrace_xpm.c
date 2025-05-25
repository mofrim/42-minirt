/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_xpm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:23:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 12:56:04 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "xpm.h"

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

	cx = mrt.can_params.pixel_minx;
	px_colr = *mrt.scene->alight;
	while (cx < mrt.can_params.pixel_maxx)
	{
		cy = mrt.can_params.pixel_miny;
		while (cy < mrt.can_params.pixel_maxy)
		{
			if (!(cy % mrt.scene->subsample) || \
cy == mrt.can_params.pixel_miny || cx == mrt.can_params.pixel_minx)
			{
				ray_dir = canvas2viewport(cx, cy, *mrt.scene->cam);
				px_colr = traceray(*mrt.scene, ray_dir);
			}
			put_pixel_xpm(mrt, cx, cy, px_colr);
			cy++;
		}
		cx++;
	}
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.xc->img,
		mrt.can_params.sidebarx, 0);
}
