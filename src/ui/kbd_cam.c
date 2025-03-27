/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:05:37 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/24 15:18:15 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keycodes.h"

/* Handle the camera rotations via `wasd` keys. First the new roation matrix is
 * calculated and then the orient vector is updated correspopndingly. For
 * calculation details see those functions. */
// TODO: maybe put get_new_rot and update_orient into one func because they
// belong together and one does not make much sense wihtout the other.
void	handle_cam_rot_keys(int key, t_mrt mrt)
{
	if (key == 119)
	{
		mrt.scene->cam->rot = cam_get_new_rot(mrt.scene->cam->rot, 0.075, 0);
		mrt.scene->cam->orient = cam_update_orient(*mrt.scene->cam);
		redraw_win(mrt);
	}
	else if (key == 115)
	{
		mrt.scene->cam->rot = cam_get_new_rot(mrt.scene->cam->rot, -0.075, 0);
		mrt.scene->cam->orient = cam_update_orient(*mrt.scene->cam);
		redraw_win(mrt);
	}
	else if (key == 97)
	{
		mrt.scene->cam->rot = cam_get_new_rot(mrt.scene->cam->rot, 0, 0.075);
		mrt.scene->cam->orient = cam_update_orient(*mrt.scene->cam);
		redraw_win(mrt);
	}
	else if (key == 100)
	{
		mrt.scene->cam->rot = cam_get_new_rot(mrt.scene->cam->rot, 0, -0.075);
		mrt.scene->cam->orient = cam_update_orient(*mrt.scene->cam);
		redraw_win(mrt);
	}
}

/* Make the cam move into dir given via arrow keys: UP -> forth, LEFT -> left,
 * ...
 * TODO: add a `ang_step` and `dir_step` var to t_camera in order to be able to
 * control the correspopnding step sizes via other shortcuts.
 */
void	handle_cam_dir_keys(int key, t_mrt mrt)
{
	if (key == KEY_UP)
	{
		printf("move pos forth\n");
		mrt.scene->cam->pos = cam_get_new_pos(mrt.scene->cam, FORTH, 0.4);
		redraw_win(mrt);
	}
	else if (key == KEY_DOWN)
	{
		printf("move pos back\n");
		mrt.scene->cam->pos = cam_get_new_pos(mrt.scene->cam, BACK, 0.4);
		redraw_win(mrt);
	}
	else if (key == KEY_LEFT)
	{
		printf("move pos left\n");
		mrt.scene->cam->pos = cam_get_new_pos(mrt.scene->cam, LEFT, 0.4);
		redraw_win(mrt);
	}
	else if (key == KEY_RIGHT)
	{
		printf("move pos right\n");
		mrt.scene->cam->pos = cam_get_new_pos(mrt.scene->cam, RIGHT, 0.4);
		redraw_win(mrt);
	}
}
