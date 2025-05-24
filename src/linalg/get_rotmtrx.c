/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rotmtrx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:16:02 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 09:19:56 by fmaurer          ###   ########.fr       */
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
