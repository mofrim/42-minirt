/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:23:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 12:35:30 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	canvas2viewport(double cx, double cy, t_camera cam);
t_colr	traceray(t_scene scene, t_v3 ray_dir);

/**
 * The main raytracing routine.
 *
 * So far this is complete. Any further development should be happening in the
 * subroutines.
 */
void	raytrace(t_mrt mrt)
{
	int		cx;
	int		cy;
	t_v3	ray_dir;
	t_colr	px_colr;

	cx = mrt.can_params.pixel_minx;
	px_colr = *mrt.scene->alight;
	while (cx < mrt.can_params.pixel_maxx)
	{
		cy = mrt.can_params.pixel_miny;
		while (cy < mrt.can_params.pixel_maxy)
		{
			ray_dir = canvas2viewport(cx, cy, *mrt.scene->cam);
			if (!(cy % mrt.scene->subsample))
				px_colr = traceray(*mrt.scene, ray_dir);
			put_pixel_canvas_rt(mrt, (t_pxl){cx, cy}, px_colr);
			cy++;
		}
		cx++;
	}
}

void	raytrace_pthread(t_mrt mrt);

/* Dispatch the raytracing to the function that is currently asked. */
void	launch_raytrace(t_mrt mrt)
{
	if (mrt.rtfunc == RT_XPM)
		raytrace_xpm(mrt);
	else if (mrt.rtfunc == RT_PXPUT)
		raytrace(mrt);
	else if (THREADS > 1 && (mrt.rtfunc == RT_PTHREAD_PXPUT || \
mrt.rtfunc == RT_PTHREAD_XPM))
		raytrace_pthread(mrt);
}
