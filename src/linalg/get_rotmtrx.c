/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rotmtrx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:16:02 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 09:54:00 by fmaurer          ###   ########.fr       */
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
// FIXME: handle orient = {0, 0, -1}. And maybe test a little bit more if this
// is really bullet proof...
t_mtrx	get_rotmtrx(t_v3 orient)
{
	t_v3	rot_axis;
	double	rot_angle;
	t_mtrx	id;
	t_mtrx	cross_matrix;
	t_mtrx	rot;

	rot_axis = v3_normalize(v3_cross((t_v3){0, 0, 1}, orient));
	rot_angle = acos(v3_dot((t_v3){0, 0, 1}, orient));
	id = mtrx_new((t_v3){1, 0, 0}, (t_v3){0, 1, 0}, (t_v3){0, 0, 1});
	cross_matrix = mtrx_new((t_v3){0, rot_axis.z, -rot_axis.y},
			(t_v3){-rot_axis.z, 0, rot_axis.x},
			(t_v3){rot_axis.y, -rot_axis.x, 0});
	rot = mtrx_add_mtrx(mtrx_add_mtrx(id, mtrx_mult_scalar(cross_matrix,
					sin(rot_angle))),
			mtrx_mult_scalar(mtrx_prod_mtrx(cross_matrix, cross_matrix),
				1 - cos(rot_angle)));
	return (rot);
}
