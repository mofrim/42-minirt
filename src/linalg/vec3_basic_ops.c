/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:33:53 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 10:03:55 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	add_scalar(t_vec3 *self, double d)
{
	t_vec3	v;

	v = *self;
	v.x += d;
	v.y += d;
	v.z += d;
	return (v);
}

t_vec3	add_vec(t_vec3 *self, t_vec3 w)
{
	t_vec3	v;

	v = *self;
	v.x += w.x;
	v.y += w.y;
	v.z += w.z;
	return (v);
}

t_vec3	add_vec_coords(t_vec3 *self, double x, double y, double z)
{
	t_vec3	v;

	v = *self;
	v.x += x;
	v.y += y;
	v.z += z;
	return (v);
}

t_vec3	mult(t_vec3 *self, double d)
{
	t_vec3	v;

	v = *self;
	v.x *= d;
	v.y *= d;
	v.z *= d;
	return (v);
}

/* Keep this around for maybe later use... */

// t_vec3	*add_scalar(t_vec3 *self, double d)
// {
// 	t_vec3	*v;
//
// 	v = vec3_new(self->x, self->y, self->z);
// 	v->_add_scalar(v, d);
// 	return (v);
// }
//
// t_vec3 *add_vec(t_vec3 *self, t_vec3 w)
// {
// 	t_vec3	*v;
//
// 	v = vec3_new(self->x, self->y, self->z);
// 	v->_add_vec(v, w);
// 	return (v);
// }
//
// t_vec3 *add_vec_coords(t_vec3 *self, double x, double y, double z)
// {
// 	t_vec3	*v;
//
// 	v = vec3_new(self->x, self->y, self->z);
// 	v->_add_vec_coords(v, x, y, z);
// 	return (v);
// }
//
// t_vec3	*mult(t_vec3 *self, double d)
// {
// 	t_vec3	*v;
//
// 	v = vec3_new(self->x, self->y, self->z);
// 	v->_mult(v, d);
// 	return (v);
// }
