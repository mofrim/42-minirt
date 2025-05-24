/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_toggle_sidebar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:55:02 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 17:29:08 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keycodes.h"

void	handle_toggle_sidebar(int key, t_mrt *mrt)
{
	if (key == KEY_SLASH)
	{
		mrt->show_sidebar = !mrt->show_sidebar;
		if (mrt->show_sidebar == false)
		{
			mlx_clear_window(mrt->mlx, mrt->win);
			mlx_destroy_image(mrt->mlx, mrt->xc->img);
			free(mrt->xc);
			mrt->xc = init_xpm_canvas(mrt->mlx, WINX, WINY);
			mrt->can_params.canvas_width = WINX;
			mrt->can_params.pixel_minx = -WINX / 2;
			mrt->can_params.pixel_maxx = WINX / 2;
			mrt->can_params.canvas_offset_x = WINX / 2;
			mrt->can_params.sidebarx = 0;
			mrt->scene->cam->cvr = mrt->scene->cam->view_width / WINX;
			launch_raytrace(*mrt);
		}
		else
		{
			mlx_clear_window(mrt->mlx, mrt->win);
			mlx_destroy_image(mrt->mlx, mrt->xc->img);
			free(mrt->xc);
			mrt->xc = init_xpm_canvas(mrt->mlx, CANVAS_WIDTH, WINY);
			mrt->can_params.canvas_width = CANVAS_WIDTH;
			mrt->can_params.pixel_minx = -CANVAS_WIDTH / 2;
			mrt->can_params.pixel_maxx = CANVAS_WIDTH / 2;
			mrt->can_params.canvas_offset_x = SIDEBAR_AREA_X + CANVAS_WIDTH / 2;
			mrt->can_params.sidebarx = SIDEBAR_AREA_X;
			mrt->scene->cam->cvr = mrt->scene->cam->view_width / CANVAS_WIDTH;
			launch_raytrace(*mrt);
			show_sidebar(*mrt);
		}
	}
}
