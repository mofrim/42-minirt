/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:22:32 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/05 11:11:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// QUESTION: can this go wrong?
static double	triag_area(t_v3 u, t_v3 v)
{
	return (0.5 * v3_norm(v3_cross(u, v)));
}

// QUESTION: can this go wrong?
static double	subtriag_area_sum(t_v3 x, t_triangle tri)
{
	double	ar1;
	double	ar2;
	double	ar3;

	ar1 = triag_area(v3_minus_vec(x, tri.b), v3_minus_vec(x, tri.a));
	ar2 = triag_area(v3_minus_vec(x, tri.c), v3_minus_vec(x, tri.a));
	ar3 = triag_area(v3_minus_vec(x, tri.c), v3_minus_vec(x, tri.b));
	return (ar1 + ar2 + ar3);
}

/**
 * The Triangle-Ray intersection.
 *
 * When lies a point inside the triangle? Iff the sum of the areas of the 3
 * triangle this point and 2 of the main triangles points make up is equal to
 * the main triangles area: A = 1/2 * g * h = 1/2 * |(AB x AC)|, where 'x' is
 * the cross product. The last equality holds because the result of the cross
 * product is equal to the area of the parallelogram that they form.
 *
 * When lies a point x on a plane? Iff <(x - P), n> = 0, where `P` is any point
 * on the plane (so f.ex. `tri.a` in the triangle case) and `n` is the planes
 * normal vec.
 *
 */
double	triangle_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_triangle tri)
{
	t_v3	x;
	double	t;
	double	rn;

	rn = v3_dot(ray_dir, tri.normal);
	if (rn == 0)
		return (INF);
	t = (tri.potdn - v3_dot(origin, tri.normal)) / rn;
	x = v3_add_vec(origin, v3_mult(ray_dir, t));
	// FIXME: dirty numerical hack to limit the number of decimals being
	// compared. otherwise stuff like
	// 		v3-x with inf: (0.048371387560256, 0.188943859017517, -2.000000000000000)
	// 		subtriag_area_sum(x, tri) = 32.000000000000007
	// 		tri.area = 32.000000000000000
	// will lead to INF being returned even though the point lies inside the
	// triangle!
	if ((float)subtriag_area_sum(x, tri) > (float)tri.area)
	{
		// if (fabs(x.x) < 1 && fabs(x.y) < 1 && x.z == -2)
		// {
		// 	printf("v3-%s: (%.15lf, %.15lf, %.15lf)\n", "x with inf", x.x, x.y, x.z);
		// 	printf("subtriag_area_sum(x, tri) = %.15lf\n", subtriag_area_sum(x, tri));
		// 	printf("tri.area = %.15lf\n", tri.area);
		// }
		return (INF);
	}
	if (rp.tmin <= t && t < rp.tmax)
		return (t);
	return (INF);
}

/* Returns the color of the sphere at the hitpoint. So far only for ambient and
 * diffuse lighting. */
t_colr	triangle_get_colr(t_scene scene, t_triangle tri, t_v3 hitpoint)
{
	t_v3	normal_vec;
	t_colr	colr_at_hitpoint;

	normal_vec = v3_get_norm(tri.normal);
	colr_at_hitpoint = calculate_lights(scene, hitpoint, normal_vec, tri.colr);
	return (colr_at_hitpoint);
}
