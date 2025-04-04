/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:33:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/04 11:09:23 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Intersect ray with the sphere. */
// QUESTION: is returning the smaller of both solutions a good approach? It
// might also be possible that one of them is smaller than 0, thus it it is
// invalid and the other, even though it is greater, is the correct one!
// ANSWER: mitigated this for now by checking inside of this function, but maybe
// it have to think about this more later....
double	sphere_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_sphere *sphere)
{
	t_v2	res;
	t_v3	co;
	t_v3	abc;
	double	disc;

	co = v3_add_vec(origin, v3_mult(sphere->center, -1));
	abc.x = v3_dot(ray_dir, ray_dir);
	abc.y = 2 * v3_dot(co, ray_dir);
	abc.z = v3_dot(co, co) - sphere->r_squared;
	disc = abc.y * abc.y - 4 * abc.x * abc.z;
	if (disc < 0)
		return (INF);
	res.x1 = (-abc.y + sqrt(disc)) / (2 * abc.x);
	res.x2 = (-abc.y - sqrt(disc)) / (2 * abc.x);
	if (rp.tmin < res.x1 && res.x1 < rp.tmax && res.x1 < res.x2)
		return (res.x1);
	if (rp.tmin < res.x2 && res.x2 < rp.tmax)
		return (res.x2);
	return (INF);
}

/* Returns the normal vector on the sphere at a given hitpoint. */
static t_v3	get_normal_sphere(t_v3	hitpoint, t_v3 center)
{
	return (v3_get_norm(v3_add_vec(hitpoint, v3_mult(center, -1))));
}

/* Returns the color of the sphere at the hitpoint. So far only for ambient and
 * diffuse lighting. */
t_colr	sphere_get_colr(t_scene scene, t_sphere s, t_v3 hitpoint)
{
	t_v3	normal_vec;
	t_colr	colr_at_hitpoint;

	normal_vec = get_normal_sphere(hitpoint, s.center);
	colr_at_hitpoint = calculate_lights(scene, hitpoint, normal_vec, s.colr);
	return (colr_at_hitpoint);
}
