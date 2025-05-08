/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_products.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:13:45 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 10:04:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* The dot product - Vec3 class func.  */
double	dot(t_vec3 *self, t_vec3 w)
{
	return (self->x * w.x + self->y * w.y + self->z * w.z);
}

/* The dot product. Standalone function. Takes 2 Vec3's and returns their
 * dot-product. */
double	vec3_dot(t_vec3 v, t_vec3 w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

/* The cross product - Vec3 class func. For usage in assignments or direct
 * calculations. */
t_vec3	cross(t_vec3 *self, t_vec3 w)
{
	t_vec3	v;
	t_vec3	u;

	v = *self;
	u = *self;
	v.x = u.y * w.z - u.z * w.y;
	v.y = u.z * w.x - u.x * w.z;
	v.z = u.x * w.y - u.y * w.x;
	return (v);
}

/* The cross product for usage in assignments or direct calculations. */
t_vec3	vec3_cross(t_vec3 u, t_vec3 w)
{
	t_vec3	v;

	v = u;
	v.x = u.y * w.z - u.z * w.y;
	v.y = u.z * w.x - u.x * w.z;
	v.z = u.x * w.y - u.y * w.x;
	return (v);
}

/* The cross product with allocation. Returns a pointer to the resuting vector
 * from the cross product of both input vecs. */
t_vec3	*vec3_cross_alloc(t_vec3 u, t_vec3 w)
{
	t_vec3	*v;

	v = malloc(sizeof(t_vec3));
	*v = u;
	v->x = v->y * w.z - v->z * w.y;
	v->y = v->z * w.x - v->x * w.z;
	v->z = v->x * w.y - v->y * w.x;
	return (v);
}
