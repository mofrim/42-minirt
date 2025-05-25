/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:05:01 by zrz               #+#    #+#             */
/*   Updated: 2025/05/25 18:59:08 by fmaurer          ###   ########.fr       */
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
double	plane_intersect_ray(
		t_v3 origin,
		t_v3 ray_dir,
		t_ray_minmax rp,
		t_plane *plane)
{
	double	denominator;
	double	t;
	t_v3	p0_l0;

	denominator = v3_dot(ray_dir, plane->normal);
	if (fabs(denominator) > EPS)
	{
		p0_l0 = v3_minus_v3(plane->pop, origin);
		t = v3_dot(p0_l0, plane->normal) / denominator;
		if (rp.tmin <= t && t < rp.tmax)
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
t_colr	plane_get_colr(t_scene scene, t_objlst pobj, t_v3 hit)
{
	t_plane	p;
	t_colr	colr_at_hitpoint;
	t_hp	hp;

	p = *(t_plane *)pobj.obj;
	hp.loc = hit;
	hp.cam2hp = v3_normalize(v3_minus_v3(scene.cam->pos, hit));
	hp.scolr = plane_get_scolr(p, hp.loc);
	hp.spec = p.spec;
	if (v3_dot(p.normal, v3_mult(hp.cam2hp, -1)) < 0)
		hp.normal = p.normal;
	else
		hp.normal = v3_mult(p.normal, -1);
	colr_at_hitpoint = calculate_lights(scene, hp);
	return (colr_at_hitpoint);
}
