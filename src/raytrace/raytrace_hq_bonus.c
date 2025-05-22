/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_hq_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 23:33:49 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/23 00:03:15 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bonus.h"

/* The supersampling-xpm thread routine. */
void	*rt_hq_thread_xpm(void *args)
{
	t_thread_args	*ta;
	int				cx;
	int				cy;
	t_colr			pxcolr;

	ta = (t_thread_args *)args;
	cx = ta->x_start - 1;
	while (++cx <= ta->x_end)
	{
		cy = PIXEL_MINY - 1;
		while (++cy < PIXEL_MAXY)
		{
			pxcolr = supersample_pixel(cx, cy, *ta->mrt->scene);
			put_pixel_xpm(ta->mrt->xc, cx, cy, pxcolr);
		}
		if (!(cx % 30))
			ft_printf(".");
	}
	return (NULL);
}

// FIXME names ?!?!!?
void	raytrace_hq_pthread_xpm(t_mrt mrt, int step, int last_step,
		pthread_t *threads)
{
	int				i;
	int				j;
	t_thread_args	*params;

	params = malloc(sizeof(t_thread_args) * THREADS);
	j = PIXEL_MINX;
	i = 0;
	while (i < THREADS - 1)
	{
		params[i] = (t_thread_args){&mrt, j, j + step, NULL};
		j += step + 1;
		pthread_create(&threads[i], NULL, rt_hq_thread_xpm, &params[i]);
		i++;
	}
	params[i] = (t_thread_args){&mrt, j, j + last_step, NULL};
	pthread_create(&threads[i], NULL, rt_hq_thread_xpm, &params[i]);
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.xc->img, SIDEBAR_AREA_X, 0);
	ft_printf(" done.\n");
	free(params);
}

void	raytrace_hq_pthread(t_mrt mrt)
{
	int				step;
	int				last_step;
	pthread_t		threads[THREADS];

	step = CANVAS_WIDTH / THREADS;
	if (THREADS * step < CANVAS_WIDTH)
		last_step = step - CANVAS_WIDTH % THREADS + 1;
	else
		last_step = step + CANVAS_WIDTH % THREADS;
	raytrace_hq_pthread_xpm(mrt, step, last_step, threads);
}
