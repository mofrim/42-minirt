/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rotmtrx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:16:02 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 00:31:54 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Get the rotation from the given orientation vector
 *
 * Actually functioning version... the idea is simple: the orientation vector
 * read from scenefile is supposed to be the new forth-direction. So we
 * construct a new coordinate system using the world-axes ensuring that (0,1,0)
 * is still the up direction in the new coordinate system. There is one
 * edge-case where forth is almost parallel to (0,1,0). in this case we need to
 * construct a right vector using x- or z-axis (could also be any other vector
 * not parallel to axis). Finally the transformation matrix from world to camera
 * coordinates is contructed.
 */
t_mtrx	get_rotmtrx(t_v3 orient)
{
	t_v3	world_up;
	t_v3	right;
	t_v3	up;
	t_mtrx	rot;

	world_up = (t_v3){0, 1, 0};
	if (fabs(v3_dot(orient, world_up)) > 0.999)
	{
		right = v3_normalize(v3_cross(orient, (t_v3){1, 0, 0}));
		if (v3_norm(right) < 0.001)
			right = v3_normalize(v3_cross(orient, (t_v3){0, 0, 1}));
	}
	else
		right = v3_normalize(v3_cross(orient, world_up));
	up = v3_cross(right, orient);
	rot = mtrx_new(v3_mult(right, -1), up, orient);
	return (rot);
}

/* Old flawed version using Rodrigues formula. */
// t_mtrx	get_rotmtrx(t_v3 orient)
// {
// 	t_v3	rot_axis;
// 	double	rot_angle;
// 	t_mtrx	id;
// 	t_mtrx	cross_matrix;
// 	t_mtrx	rot;
//
// 	rot_axis = v3_normalize(v3_cross((t_v3){0, 0, 1}, orient));
// 	rot_angle = acos(v3_dot((t_v3){0, 0, 1}, orient));
// 	id = mtrx_new((t_v3){1, 0, 0}, (t_v3){0, 1, 0}, (t_v3){0, 0, 1});
// 	cross_matrix = mtrx_new(
// 			(t_v3){0, rot_axis.z, -rot_axis.y},
// 			(t_v3){-rot_axis.z, 0, rot_axis.x},
// 			(t_v3){rot_axis.y, -rot_axis.x, 0});
// 	rot = mtrx_add_mtrx(mtrx_add_mtrx(id, mtrx_mult_scalar(cross_matrix,
// 					sin(rot_angle))),
// 			mtrx_mult_scalar(mtrx_prod_mtrx(cross_matrix, cross_matrix),
// 				1 - cos(rot_angle)));
// 	return (rot);
// }
