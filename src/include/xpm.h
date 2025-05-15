/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:45:50 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/15 15:45:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_H
# define XPM_H

# include "../minilibx-linux/mlx_int.h"

/* Forward declarations. */
typedef struct s_mrt	t_mrt;
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

t_xpm_canvas	*init_xpm_canvas(t_xvar *mlx);
int				put_pixel_xpm(t_xpm_canvas *xc, int x, int y, t_colr colr);
void			raytrace_xpm(t_mrt mrt);
void			raytrace_xpm_aa(t_mrt mrt);

#endif

