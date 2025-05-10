/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:29:10 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/10 18:41:14 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Returns the closest intersection found in all scene objects.
 *
 * This scans through all objects in the scene for a intersection. For the
 * object-dependent intersection calculations dispatches to the
 * intersect_ray_obj() func.
 */
t_intersec	intersect_ray_objs(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_objlst *objs)
{
	double		t;
	t_intersec	intersec;

	intersec.t = INF;
	intersec.obj = NULL;
	while (objs)
	{
		if (objs->type != LIGHT)
		{
			t = intersect_ray_single_obj(origin, ray_dir, rp, objs);
			if (rp.tmin < t && t < rp.tmax && t < intersec.t)
				intersec = (t_intersec){t, objs};
		}
		objs = objs->next;
	}
	return (intersec);
}

/* Generalized ray obj intersection function. Dispatches to the specific object
 * type intersection function. */
// TODO homegenize func params (maybe all obj->obj)
double	intersect_ray_single_obj(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_objlst *obj)
{
	if (obj->type == SPHERE)
		return (sphere_intersect_ray(origin, ray_dir, rp, obj->obj));
	else if (obj->type == CIRCLE)
		return (circle_intersect_ray(origin, ray_dir, rp,
				*(t_circle *)obj->obj));
	else if (obj->type == TRIANGLE)
		return (triangle_intersect_ray(origin, ray_dir, rp,
				*(t_triangle *)obj->obj));
	else if (obj->type == CYLINDER)
		return (cylinder_intersect_ray(origin, ray_dir, rp, obj->obj));
	else if (obj->type == PLANE)
		return (plane_intersect_ray(origin, ray_dir, rp, obj->obj));
	return (0);
}
