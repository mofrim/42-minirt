/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:45:50 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 17:33:22 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_H
# define XPM_H

# include "../minilibx-linux/mlx_int.h"

/* Forward declarations. */
typedef struct s_mrt	t_mrt;
typedef struct s_scene	t_scene;
typedef struct s_colr	t_colr;

typedef struct s_xpm_canvas
{
	t_xvar			*mlx;
	void			*img;
	unsigned char	*data;
	int				bpp;
	int				opp;
	int				xpm_line_len;
	int				endian;
}	t_xpm_canvas;

t_xpm_canvas	*init_xpm_canvas(t_xvar *mlx, int width, int height);
int				put_pixel_xpm(t_mrt mrt, int x, int y, t_colr colr);
void			raytrace_xpm(t_mrt mrt);
void			raytrace_xpm_hq(t_mrt mrt);
t_colr			supersample_pixel(int cx, int cy, t_scene scene);

# ifdef BONUS

void			raytrace_hq_pthread(t_mrt mrt);
# endif

#endif
