/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rotmtrx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:16:02 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/23 16:59:33 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Get the rotation from the given orientation vector
 *
 * Our assumption is that the original camera orientation was to be aligned with
 * xy-axes and to look at (0, 0, 1) which is positive z-dir. In here we use the
 * Rodrigues formula to calc the rotation matrix from this assumption.
 * Orient has to be normalized!
 */
// t_mtrx	get_rotmtrx(t_v3 orient)
// {
// 	t_v3	rot_axis;
// 	double	rot_angle;
// 	t_mtrx	id;
// 	t_mtrx	cross_matrix;
// 	t_mtrx	rot;
//
// 	if (orient.x == 0 && orient.y == 0 && orient.z == -1)
// 	{
// 		rot = mtrx_new((t_v3){-1, 0, 0}, (t_v3){0, 1, 0}, (t_v3){0, 0, -1});
// 		return (rot);
// 	}
// 	rot_axis = v3_normalize(v3_cross((t_v3){0, 0, 1}, orient));
// 	rot_angle = acos(v3_dot((t_v3){0, 0, 1}, orient));
// 	printf("rot_angle: %f\n", rot_angle);
// 	v3_print(rot_axis, "rot axis");
// 	id = mtrx_new((t_v3){1, 0, 0}, (t_v3){0, 1, 0}, (t_v3){0, 0, 1});
// 	cross_matrix = mtrx_new((t_v3){0, rot_axis.z, -rot_axis.y},
// 			(t_v3){-rot_axis.z, 0, rot_axis.x},
// 			(t_v3){rot_axis.y, -rot_axis.x, 0});
// 	rot = mtrx_add_mtrx(mtrx_add_mtrx(id, mtrx_mult_scalar(cross_matrix,
// 					sin(rot_angle))),
// 			mtrx_mult_scalar(mtrx_prod_mtrx(cross_matrix, cross_matrix),
// 				1 - cos(rot_angle)));
// 	rot_angle = 1.31;
// 	t_mtrx rot2 = mtrx_new((t_v3){cos(rot_angle), sin(rot_angle), 0}, (t_v3){-sin(rot_angle), cos(rot_angle), 0}, (t_v3){0, 0, 1});
// 	rot = mtrx_prod_mtrx(rot, rot2);
// 	return (rot);
// }

t_mtrx	get_rotmtrx(t_v3 orient)
{
	t_mtrx	rot;

	if (orient.x == 0 && orient.y == 0 && orient.z == -1)
	{
		rot = mtrx_new((t_v3){-1, 0, 0}, (t_v3){0, 1, 0}, (t_v3){0, 0, -1});
		return (rot);
	}
	double x_ang = asin(orient.y);
	printf("x_ang = %f\n", x_ang);
	t_mtrx rotx = mtrx_new((t_v3){1, 0, 0}, (t_v3){0, cos(x_ang), -sin(x_ang)},
			(t_v3){0, sin(x_ang), cos(x_ang)});
	double y_ang = asin(orient.x / sin(x_ang));
	if (x_ang == 0)
		y_ang = 0;
	printf("y_ang = %f\n", y_ang);
	// t_mtrx rotz = mtrx_new((t_v3){cos(y_ang), sin(y_ang), 0}, (t_v3){-sin(y_ang), cos(y_ang), 0}, (t_v3){0, 0, 1});
	t_mtrx rotz = mtrx_new((t_v3){cos(y_ang), 0, sin(y_ang)}, (t_v3){0, 1, 0},
			(t_v3){-sin(y_ang), 0, cos(y_ang)});
	rot = mtrx_prod_mtrx(rotz, rotx);
	return (rot);
}
