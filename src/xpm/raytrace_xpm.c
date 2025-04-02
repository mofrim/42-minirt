/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_xpm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:23:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/02 14:33:33 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "xpm.h"

t_v3	canvas2viewport(int cx, int cy, t_camera cam);
t_colr	traceray(t_scene scene, t_v3 ray_dir);

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
