/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:05:37 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/18 21:24:33 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keycodes.h"

/* Handle the camera rotations via `wasd` keys. First the new roation matrix is
 * calculated and then the orient vector is updated correspopndingly. For
 * calculation details see those functions. */
void	handle_cam_rot_keys(int key, t_mrt mrt)
{
	if (key == KEY_W)
	{
		update_cam_rot_orient(mrt.scene->cam, 0.075, 0);
		redraw_win(mrt, false);
	}
	else if (key == KEY_A)
	{
		update_cam_rot_orient(mrt.scene->cam, 0, 0.075);
		redraw_win(mrt, false);
	}
	else if (key == KEY_S)
	{
		update_cam_rot_orient(mrt.scene->cam, -0.075, 0);
		redraw_win(mrt, false);
	}
	else if (key == KEY_D)
	{
		update_cam_rot_orient(mrt.scene->cam, 0, -0.075);
		redraw_win(mrt, false);
	}
}

/* Helper function for handle_cam_dir_keys. Also updates the is_inside_obj flag
 * in case we have moved into one object. */
static void	move_cam_pos(t_scene scene, t_dirs dir, float step)
{
	scene.cam->pos = cam_get_new_pos(scene.cam, dir, step);
	scene.cam->is_inside_obj = is_cam_inside_obj(*scene.cam, scene);
}

/* Make the cam move into dir given via arrow keys: UP -> forth, LEFT -> left,
 */
void	handle_cam_dir_keys(int key, t_mrt mrt)
{
	if (key == KEY_UP)
	{
		move_cam_pos(*mrt.scene, FORTH, 0.4);
		redraw_win(mrt, false);
	}
	else if (key == KEY_DOWN)
	{
		move_cam_pos(*mrt.scene, BACK, 0.4);
		redraw_win(mrt, false);
	}
	else if (key == KEY_LEFT)
	{
		move_cam_pos(*mrt.scene, LEFT, 0.4);
		redraw_win(mrt, false);
	}
	else if (key == KEY_RIGHT)
	{
		move_cam_pos(*mrt.scene, RIGHT, 0.4);
		redraw_win(mrt, false);
	}
}
