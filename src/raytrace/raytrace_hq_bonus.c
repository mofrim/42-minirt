/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_hq_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 23:33:49 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 19:08:10 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bonus.h"

static void	execute_raytrace(t_mrt mrt, int step, int last_step,
				pthread_t *threads);
static void	*rt_hq_xpm_thread(void *args);

/* Calculate the number of lines every thread will have to trace and then
 * proceed to thread in raytrace_hq_xpm_launch_threads */
void	raytrace_hq_pthread(t_mrt mrt)
{
	int				step;
	int				last_step;
	pthread_t		threads[THREADS];
	t_canvas_params	cp;

	cp = mrt.can_params;
	step = cp.canvas_width / THREADS;
	if (THREADS * step < cp.canvas_width)
		last_step = step - cp.canvas_width % THREADS + 1;
	else
		last_step = step + cp.canvas_width % THREADS;
	execute_raytrace(mrt, step, last_step, threads);
}

/* Launches THREADS number of threads with their precalculated range of lines
 * each thread should work on. Waits for every thread to finish and puts the img
 * to the window. */
void	execute_raytrace(t_mrt mrt, int step, int last_step,
		pthread_t *threads)
{
	int				i;
	int				j;
	t_thread_args	*params;

	params = malloc(sizeof(t_thread_args) * THREADS);
	j = mrt.can_params.pixel_minx;
	i = 0;
	while (i < THREADS - 1)
	{
		params[i] = (t_thread_args){&mrt, j, j + step, NULL};
		j += step + 1;
		pthread_create(&threads[i], NULL, rt_hq_xpm_thread, &params[i]);
		i++;
	}
	params[i] = (t_thread_args){&mrt, j, j + last_step, NULL};
	pthread_create(&threads[i], NULL, rt_hq_xpm_thread, &params[i]);
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.xc->img,
		mrt.can_params.sidebarx, 0);
	ft_printf(" done.\n");
	free(params);
}

/* The hq thread routine re-using the supersample_pixel function from
 * non-multithreaded hq tracing. */
void	*rt_hq_xpm_thread(void *args)
{
	t_thread_args	*ta;
	int				cx;
	int				cy;
	t_colr			pxcolr;
	t_canvas_params	cp;

	ta = (t_thread_args *)args;
	cp = ta->mrt->can_params;
	cx = ta->x_start - 1;
	while (++cx <= ta->x_end)
	{
		cy = cp.pixel_miny - 1;
		while (++cy < cp.pixel_maxy)
		{
			pxcolr = supersample_pixel(cx, cy, *ta->mrt->scene);
			put_pixel_xpm(*ta->mrt, cx, cy, pxcolr);
		}
		if (!(cx % 30))
			ft_printf(".");
	}
	return (NULL);
}
