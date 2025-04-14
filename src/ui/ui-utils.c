/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui-utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:33:36 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/14 15:50:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_axis(t_mrt mrt)
{
	int		i;
	t_colr	c;

	c = (t_colr){42, 42, 42, 0.5};
	i = -1;
	while (++i < CANVAS_WIDTH)
	{
		put_pixel_canvas_rt(mrt, (t_pxl){i, 0}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){-i, 0}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){0, i}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){0, -i}, c);
	}
}
