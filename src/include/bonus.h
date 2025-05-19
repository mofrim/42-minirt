/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:03:29 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/19 23:38:14 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <pthread.h>

/* Forward declarations. */
typedef struct s_mrt	t_mrt;
typedef struct s_colr	t_colr;
typedef struct s_pxl	t_pxl;

typedef struct s_thread_args
{
	t_mrt			*mrt;
	int				x_start;
	int				x_end;
	pthread_mutex_t	*mlx_lock;
}	t_thread_args;

void	raytrace_pthread(t_mrt mrt);
void	*rt_thread_xpm(void *args);
void	*rt_thread_pxput(void *args);
void	put_pixel_canvas_pthread(t_mrt mrt, t_pxl pos, t_colr pxlcolr,
			pthread_mutex_t *mlx_lock);

#endif
