/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_get_new_pos_rot.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:20:18 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 10:05:47 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Calculate new rotation matrix for use in cam struct.
 *
 * For interactively controlling the cameras angle this function returns the
 * matrix product of camera_rot_mtrx * rot_x/y. Only one rotation is executed in
 * here with precedence to rot_y. Meaning: if y_ang aka 2nd arg != 0 then only
 * the rotation around y-axis is applied before the rotation specified via
 * orient vector. The matrices specified for each condition is in the first case
 * a rotation matrix about the x-axis, and 2ndly for the y-axis.
 */
static t_mtrx	cam_get_new_rot(t_mtrx oldrot, double x_ang, double y_ang,
					double z_ang)
{
	t_mtrx	rot;

	if (x_ang)
		rot = mtrx_new((t_v3){1, 0, 0}, (t_v3){0, cos(x_ang), -sin(x_ang)},
				(t_v3){0, sin(x_ang), cos(x_ang)});
	else if (y_ang)
		rot = mtrx_new((t_v3){cos(y_ang), 0, sin(y_ang)}, (t_v3){0, 1, 0},
				(t_v3){-sin(y_ang), 0, cos(y_ang)});
	else
		rot = mtrx_new((t_v3){cos(z_ang), -sin(z_ang), 0},
				(t_v3){sin(z_ang), cos(z_ang), 0}, (t_v3){0, 0, 1});
	return (mtrx_prod_mtrx(oldrot, rot));
}

/**
 * Update the cam rot matrix and orient v3.
 *
 * The assumption stays the same: originally orientation of camera was to look
 * at {0, 0, 1}. So in order to get the new orientation vector after the camera
 * was tilted, we simply compute the rotation of the {0,0,1} vector by the new
 * rot matrix.
 */
void	update_cam_rot_orient(t_camera *cam, double x_ang, double y_ang,
			double z_ang)
{
	cam->rot = cam_get_new_rot(cam->rot, x_ang, y_ang, z_ang);
	cam->orient = mtrx_prod_v3(cam->rot, (t_v3){0, 0, 1});
}

/**
 * Get the new camera position for a move in one dir.
 *
 * For the back/forth dirs the case is pretty simple: `forth` is always in the
 * cameras orientation vector dir, so back is opposite to this. For left and
 * right the case is almost as simple: the orig orientation was {0,0,1} so right
 * was originally {1,0,0} aka the dir along pos x-axis. So if after the rotation
 * of the camera the z-axis corrsponds to the orientation vector which is
 * rot_mtrx * {0,0,1}, the rotated x-axis corresponds to rot_mtrx * {1, 0, 0},
 * aka the rotation of the x-axis by rot_mtrx. And that is simply the first
 * column of rot_mtrx!
 */
// TODO: make step size controllable from the outside.
t_v3	cam_get_new_pos(t_camera *cam, t_dirs dir, double step)
{
	t_v3	x;
	t_v3	new_pos;

	new_pos = cam->pos;
	x = (t_v3){cam->rot.m[0][0], cam->rot.m[1][0], cam->rot.m[2][0]};
	if (dir == LEFT)
		new_pos = v3_add_vec(cam->pos, v3_mult(x, -step));
	if (dir == RIGHT)
		new_pos = v3_add_vec(cam->pos, v3_mult(x, step));
	if (dir == FORTH)
		new_pos = v3_add_vec(cam->pos, v3_mult(cam->orient, step));
	if (dir == BACK)
		new_pos = v3_add_vec(cam->pos, v3_mult(cam->orient, -step));
	return (new_pos);
}
