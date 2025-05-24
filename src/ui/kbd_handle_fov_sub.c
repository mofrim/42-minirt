/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_handle_fov_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:20:22 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 16:56:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keycodes.h"

/* Handle changes in subsampling via `{}` keys. */
void	handle_subsample(int key, t_mrt mrt)
{
	if (key == KEY_LCBRACE && mrt.scene->subsample > 1)
	{
		mrt.scene->subsample -= 1;
		redraw_win(mrt, false);
	}
	else if (key == KEY_RCBRACE && mrt.scene->subsample < 100)
	{
		mrt.scene->subsample++;
		redraw_win(mrt, false);
	}
	else if (key == KEY_1)
	{
		mrt.scene->subsample = 1;
		redraw_win(mrt, true);
	}
	else if (key == KEY_2)
	{
		mrt.scene->subsample = 10;
		redraw_win(mrt, true);
	}
}

/* Handle changes in fov via `()` keys. */
void	handle_fov(int key, t_mrt mrt)
{
	t_camera	*cam;

	cam = mrt.scene->cam;
	if (key == KEY_9 && (cam->fov - 0.1 > 0))
	{
		cam->fov -= 0.1;
		cam->view_width = 2 * VIEWZ * tan(cam->fov / 2);
		cam->cvr = cam->view_width / mrt.can_params.canvas_width;
		redraw_win(mrt, false);
	}
	if (key == KEY_0 && (cam->fov + 0.1 < M_PI))
	{
		cam->fov += 0.1;
		cam->view_width = 2 * VIEWZ * tan(cam->fov / 2);
		cam->cvr = cam->view_width / mrt.can_params.canvas_width;
		redraw_win(mrt, false);
	}
}
