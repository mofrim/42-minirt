/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:33:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 18:59:08 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Intersect ray with the sphere. */
double	sphere_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_sphere *sphere)
{
	t_v2	res;
	t_v3	co;
	t_v3	abc;
	double	disc;

	co = v3_minus_v3(origin, sphere->center);
	abc.x = v3_dot(ray_dir, ray_dir);
	abc.y = 2 * v3_dot(co, ray_dir);
	abc.z = v3_dot(co, co) - sphere->r_squared;
	disc = abc.y * abc.y - 4 * abc.x * abc.z;
	if (disc < 0)
		return (INF);
	res.x1 = (-abc.y + sqrt(disc)) / (2 * abc.x);
	res.x2 = (-abc.y - sqrt(disc)) / (2 * abc.x);
	if (rp.tmin < res.x1 && res.x1 < rp.tmax && (res.x1 < res.x2 || \
!(rp.tmin < res.x2 && res.x2 < rp.tmax)))
		return (res.x1);
	if (rp.tmin < res.x2 && res.x2 < rp.tmax)
		return (res.x2);
	return (INF);
}

/* Returns the color of the sphere at the hitpoint. */
t_colr	sphere_get_colr(t_scene scene, t_objlst sobj, t_v3 hit)
{
	t_sphere	s;
	t_colr		colr_at_hitpoint;
	t_hp		hp;

	s = *(t_sphere *)sobj.obj;
	hp.loc = hit;
	hp.cam2hp = v3_normalize(v3_minus_v3(scene.cam->pos, hit));
	hp.scolr = sphere_get_scolr(s, hp.loc);
	hp.spec = s.spec;
	hp.normal = sphere_get_normal(hp.loc, s, scene);
	colr_at_hitpoint = calculate_lights(scene, hp);
	return (colr_at_hitpoint);
}

/* The standard u/v transformation for the sphere. The + M_PI in the atan2
 * params is needed here because the value range of atan2 is [-pi, pi]. */
t_uv	sphere_get_uv(t_sphere s, t_v3 hp)
{
	t_uv	res;

	hp = v3_normalize(v3_minus_v3(hp, s.center));
	res.u = (atan2(hp.z, hp.x) + M_PI) / (2 * M_PI);
	res.v = acos(hp.y) / M_PI;
	return (res);
}
