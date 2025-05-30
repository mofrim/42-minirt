/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_thread_funcs_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:26:37 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 13:30:13 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "minirt.h"

/* The xpm thread routine. */
void	*rt_thread_xpm(void *args)
{
	t_thread_args	*ta;
	int				cx;
	int				cy;
	t_v3			ray_dir;
	t_colr			px_colr;

	ta = (t_thread_args *)args;
	cx = ta->x_start - 1;
	px_colr = *ta->mrt->scene->alight;
	while (++cx <= ta->x_end)
	{
		cy = ta->mrt->can_params.pixel_miny - 1;
		while (++cy < ta->mrt->can_params.pixel_maxy)
		{
			if (!(cy % ta->mrt->scene->subsample) || \
cy == ta->mrt->can_params.pixel_miny || cx == ta->mrt->can_params.pixel_minx)
			{
				ray_dir = canvas2viewport(cx, cy, *ta->mrt->scene->cam);
				px_colr = traceray(*ta->mrt->scene, ray_dir);
			}
			put_pixel_xpm(*ta->mrt, cx, cy, px_colr);
		}
	}
	return (NULL);
}

/* The pixelput thread routine. */
void	*rt_thread_pxput(void *args)
{
	t_thread_args	*ta;
	int				cx;
	int				cy;
	t_v3			ray_dir;
	t_colr			px_colr;

	ta = (t_thread_args *)args;
	cx = ta->x_start - 1;
	px_colr = *ta->mrt->scene->alight;
	while (++cx <= ta->x_end)
	{
		cy = ta->mrt->can_params.pixel_miny - 1;
		while (++cy < PIXEL_MAXY)
		{
			if (!(cy % ta->mrt->scene->subsample) || \
cy == ta->mrt->can_params.pixel_miny || cx == ta->mrt->can_params.pixel_minx)
			{
				ray_dir = canvas2viewport(cx, cy, *ta->mrt->scene->cam);
				px_colr = traceray(*ta->mrt->scene, ray_dir);
			}
			put_pixel_canvas_pthread(*ta->mrt, (t_pxl){cx, cy}, px_colr,
				ta->mlx_lock);
		}
	}
	return (NULL);
}
