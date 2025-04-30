/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_advanced_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:13:45 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/30 18:11:46 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* The dot product - Vec3 class func.  */
double	v3_dot(t_v3 v, t_v3 w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

/* The cross product for t_v3's. */
t_v3	v3_cross(t_v3 v, t_v3 w)
{
	t_v3	u;

	u = v;
	v.x = u.y * w.z - u.z * w.y;
	v.y = u.z * w.x - u.x * w.z;
	v.z = u.x * w.y - u.y * w.x;
	return (v);
}

/* Calculate the norm of a t_v3. */
double	v3_norm(t_v3 v)
{
	return (sqrt(v3_dot(v, v)));
}

/* Returns the normalized version of a t_v3. */
t_v3	v3_normalize(t_v3 v)
{
	double	norm;

	norm = sqrt(v3_dot(v, v));
	if (norm == 0.0)
		return ((t_v3){0, 0, 0});
	return (v3_mult(v, 1.0 / norm));
}
