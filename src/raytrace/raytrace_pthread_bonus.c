/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_pthread_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:46:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 18:16:10 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "minirt.h"

/* Every thread should work on a chunk of CANVAS_WIDTH / THREADS number of
 * columns (yes, we are splitting the work x-wise because we can!). Only the
 * thread with the highest number handles CANVAS_WIDTH / THREADS + CANVAS_WIDTH
 * % THREADS. Like that no part of the scene will get left behind.  */

void	put_pixel_canvas_pthread(t_mrt mrt, t_pxl pos, t_colr pxlcolr,
		pthread_mutex_t *mlx_lock)
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
		pthread_mutex_lock(mlx_lock);
		mlx_pixel_put(mrt.mlx, mrt.win, sx, sy, tcolr_to_int(pxlcolr));
		pthread_mutex_unlock(mlx_lock);
	}
}

void	raytrace_pthread_xpm(t_mrt mrt, int step, int last_step,
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
		pthread_create(&threads[i], NULL, rt_thread_xpm, &params[i]);
		i++;
	}
	params[i] = (t_thread_args){&mrt, j, j + last_step, NULL};
	pthread_create(&threads[i], NULL, rt_thread_xpm, &params[i]);
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.xc->img,
		mrt.can_params.sidebarx, 0);
	free(params);
}

void	raytrace_pthread_pxput(t_mrt mrt, int step, int last_step,
		pthread_t *threads)
{
	int				i;
	int				j;
	t_thread_args	*params;
	pthread_mutex_t	*mlx_lock;

	mlx_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mlx_lock, NULL);
	params = malloc(sizeof(t_thread_args) * THREADS);
	j = mrt.can_params.pixel_minx;
	i = -1;
	while (++i < THREADS - 1)
	{
		params[i] = (t_thread_args){&mrt, j, j + step, mlx_lock};
		j += step + 1;
		pthread_create(&threads[i], NULL, rt_thread_pxput, &params[i]);
	}
	params[i] = (t_thread_args){&mrt, j, j + last_step, mlx_lock};
	pthread_create(&threads[i], NULL, rt_thread_pxput, &params[i]);
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
	free(params);
	free(mlx_lock);
}

void	raytrace_pthread(t_mrt mrt)
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
	if (mrt.rtfunc == RT_PTHREAD_XPM)
		raytrace_pthread_xpm(mrt, step, last_step, threads);
	else
		raytrace_pthread_pxput(mrt, step, last_step, threads);
}

/* Example for multithreading gone wrong... */

// void raytrace_pthread(t_mrt mrt)
// {
// 	int				i;
// 	int				j;
// 	int				step;
// 	int				last_step;
// 	pthread_t		threads[THREADS];
// 	t_thread_args	*params;
// 	pthread_mutex_t	*mlx_lock;
// 	void			*rt_func;
//
// 	if (mrt.rtfunc == RT_PTHREAD_PXPUT)
// 	{
// 		rt_func = rt_thread_pxput;
// 		mlx_lock = malloc(sizeof(pthread_mutex_t));
// 		pthread_mutex_init(mlx_lock, NULL);
// 		mrt.mlx->do_flush = false;
// 	}
// 	else
// 	{
// 		rt_func = rt_thread_xpm;
// 		(void)mlx_lock;
// 	}
// 	params = malloc(sizeof(t_thread_args) * THREADS);
// 	step = CANVAS_WIDTH / THREADS;
// 	if (THREADS * step < CANVAS_WIDTH)
// 		last_step = step - CANVAS_WIDTH % THREADS + 1;
// 	else
// 		last_step = step + CANVAS_WIDTH % THREADS;
// 	j = PIXEL_MINX;
// 	i = 0;
// 	while (i < THREADS - 1)
// 	{
// 		params[i] = (t_thread_args){&mrt, j, j + step, mlx_lock};
// 		j += step + 1;
// 		pthread_create(&threads[i], NULL, rt_func, &params[i]);
// 		i++;
// 	}
// 	params[i] = (t_thread_args){&mrt, j, j + last_step, mlx_lock};
// 	pthread_create(&threads[i], NULL, rt_func, &params[i]);
// 	i = 0;
// 	while (i < THREADS)
// 	{
// 		pthread_join(threads[i], NULL);
// 		i++;
// 	}
// 	if (mrt.rtfunc == RT_PTHREAD_XPM)
// 		mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.xc->img, SIDEBAR_AREA_X,
// 		0);
// 	else
// 		mlx_do_sync(mrt.mlx);
// }
// void	put_pixel_canvas_pthread(t_mrt mrt, t_pxl pos, t_colr pxlcolr,
// 		pthread_mutex_t *mlx_lock)
// {
// 	int	sx;
// 	int	sy;
//
// 	if (PIXEL_MINX < pos.x && pos.x < PIXEL_MAXX && PIXEL_MINY < pos.y && 
// pos.y < PIXEL_MAXY)
// 	{
// 		sx = CANVAS_OFFSET_X + pos.x;
// 		sy = CANVAS_OFFSET_Y - pos.y;
// 		pthread_mutex_lock(mlx_lock);
// 		mlx_pixel_put(mrt.mlx, mrt.win, sx, sy, tcolr_to_int(pxlcolr));
// 		pthread_mutex_unlock(mlx_lock);
// 	}
// }

// void	*rt_thread_pxput(void *args)
// {
// 	int		cx;
// 	int		cy;
// 	t_v3	ray_dir;
// 	t_colr	px_colr;
// 	t_thread_args	*thread_args = (t_thread_args *)args;
// 	t_mrt	*mrt = thread_args->mrt;
//
// 	cx = thread_args->x_start;
// 	px_colr = mrt->scene->alight->colr;
// 	while (cx <= thread_args->x_end)
// 	{
// 		cy = PIXEL_MINY;
// 		while (cy < PIXEL_MAXY)
// 		{
// 			if (!(cy % mrt->scene->subsample) || cy == PIXEL_MINY ||
// cx == PIXEL_MINX)
// 			{
// 				ray_dir = canvas2viewport(cx, cy, *mrt->scene->cam);
// 				px_colr = traceray(*mrt->scene, ray_dir);
// 			}
// 			put_pixel_canvas_pthread(*mrt, (t_pxl){cx, cy}, px_colr,
// 			thread_args->mlx_lock);
// 			cy++;
// 		}
// 		cx++;
// 	}
// 	return(NULL);
// }
