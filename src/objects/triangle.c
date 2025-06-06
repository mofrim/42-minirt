/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:22:32 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 20:39:50 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Calculate triag area using cross product. See explanation in main triag
 * intersect func. */
static double	triag_area(t_v3 u, t_v3 v)
{
	return (0.5 * v3_norm(v3_cross(u, v)));
}

/* Calculate the sum of all subtriangles the corner points form with the point
 * being checked for intersection. */
static double	subtriag_area_sum(t_v3 x, t_triangle tri)
{
	double	ar1;
	double	ar2;
	double	ar3;

	ar1 = triag_area(v3_minus_v3(x, tri.b), v3_minus_v3(x, tri.a));
	ar2 = triag_area(v3_minus_v3(x, tri.c), v3_minus_v3(x, tri.a));
	ar3 = triag_area(v3_minus_v3(x, tri.c), v3_minus_v3(x, tri.b));
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
 * had a dirty numerical hack to limit the number of decimals being
 * compared. otherwise stuff like
 * 	v3-x with inf: (0.048371387560256, 0.188943859017517, -2.000000000000000)
 * 	subtriag_area_sum(x, tri) = 32.000000000000007
 * 	tri.area = 32.000000000000000
 * will lead to INF being returned even though the point lies inside the
 * triangle! Now using EPS.
 */
// IDEA possible little performance boost here would be to calculate the center
// and the circumfering circle of the triangle then a quick first check for
// intersection would be to calculate the distance from the triag center and
// then compare to the circle radius.
double	triangle_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_triangle *tri)
{
	t_v3	x;
	double	t;
	double	rn;

	rn = v3_dot(ray_dir, tri->normal);
	if (rn == 0)
		return (INF);
	t = (tri->pdotn - v3_dot(origin, tri->normal)) / rn;
	x = v3_add_v3(origin, v3_mult(ray_dir, t));
	if (subtriag_area_sum(x, *tri) - tri->area > EPS)
		return (INF);
	if (rp.tmin <= t && t < rp.tmax)
		return (t);
	return (INF);
}

/** Returns the color of the triangle at the hitpoint.
 *
 * Explanation for the normal treatment: for flat surfaces like the circle and
 * the triangle we have a normal calculated or read during parsing. now it can
 * happen that this normal is not the one of the surface facing the camera. so
 * we need to select the one that is facing the cam in here. This is done by
 * calculating the dot product of the normal and the vector *from* the cam *to*
 * the hitpoint <tri.normal, cam2hit>. if dot-product < 0 this means the normal
 * is poiting towards the camera. then we take it. else flip it around 180deg.
 */
t_colr	triangle_get_colr(t_scene scene, t_objlst tobj, t_v3 hit)
{
	t_triangle	tri;
	t_colr		colr_at_hitpoint;
	t_hp		hp;

	tri = *(t_triangle *)tobj.obj;
	hp.loc = hit;
	hp.cam2hp = v3_normalize(v3_minus_v3(scene.cam->pos, hit));
	hp.scolr = tri.colr;
	hp.spec = tri.spec;
	if (v3_dot(tri.normal, v3_mult(hp.cam2hp, -1)) < 0)
		hp.normal = tri.normal;
	else
		hp.normal = v3_mult(tri.normal, -1);
	colr_at_hitpoint = calculate_lights(scene, hp);
	return (colr_at_hitpoint);
}
