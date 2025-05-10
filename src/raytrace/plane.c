/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:05:01 by zrz               #+#    #+#             */
/*   Updated: 2025/05/10 20:05:00 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculates the intersection of a ray with a plane.
 *
 * The ray-plane intersection is given by the formula:
 * t = ((plane_point - ray_origin) . plane_normal) / 
 * (ray_direction . plane_normal)
 *
 * @param origin The origin of the ray.
 * @param ray_dir The direction of the ray (must be normalized).
 * @param rp The min and max t values for valid intersection (t_ray_minmax).
 * @param plane A pointer to the t_plane object.
 * @return The distance 't' to the intersection point, or INF if no intersection
 * within the valid range.
 */
double	plane_intersect_ray(t_v3 origin, t_v3 ray_dir, \
t_ray_minmax rp, t_plane *plane)
{
	double	denominator;
	double	t;
	t_v3	p0_l0;

	denominator = v3_dot(ray_dir, plane->normal);
	if (fabs(denominator) > EPSILON)
	{
		p0_l0 = v3_minus_vec(plane->pop, origin);
		t = v3_dot(p0_l0, plane->normal) / denominator;
		if (t > rp.tmin && t < rp.tmax)
			return (t);
	}
	return (INF);
}

/**
 * @brief Calculates the color of the plane at the intersection point.
 *
 * @param scene The scene data.
 * @param pobj The object list item for the plane.
 * @param hitpoint The point of intersection on the plane.
 * @return The calculated color (t_colr) at the hitpoint.
 */
t_colr	plane_get_colr(t_scene scene, t_objlst pobj, t_v3 hitpoint)
{
	t_plane	*plane;
	t_v3	normal;

	plane = (t_plane *)pobj.obj;
	normal = plane->normal;
	return (calculate_lights(scene, hitpoint, normal, pobj));
}
