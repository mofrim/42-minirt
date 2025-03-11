/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_handle_fov_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:20:22 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/09 18:39:31 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_subsample(int key, t_mrt mrt)
{
	if (key == 91)
	{
		if (mrt.scene->subsample > 1)
			mrt.scene->subsample -= 1;
		redraw_win(mrt);
	}
	if (key == 93)
	{
		if (mrt.scene->subsample < 100)
			mrt.scene->subsample++;
		redraw_win(mrt);
	}
}

void	handle_fov(int key, t_mrt mrt)
{
	t_camera	*cam;

	cam = mrt.scene->cam;
	if (key == 57 && (cam->fov - 0.1 > 0))
	{
		cam->fov -= 0.1;
		cam->view_width = 2 * tan(cam->fov/2);
		cam->cvr = cam->view_width / CANVAS_WIDTH;
		redraw_win(mrt);
	}
	if (key == 48 && (cam->fov + 0.1 < M_PI))
	{
		cam->fov += 0.1;
		cam->view_width = 2 * tan(cam->fov/2);
		cam->cvr = cam->view_width / CANVAS_WIDTH;
		redraw_win(mrt);
	}
}

