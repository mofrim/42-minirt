/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:22:32 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 09:52:41 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * The Circle-Ray intersection calculation.
 *
 * 		<(O + t * R - C), n> = 0
 *
 * with <x,y> = scalar product, O = origin, R = ray_dir, C = center of circle, n
 * = circle normal is to be solved. This is all that is done in here.
 */
double	circle_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_circle c)
{
	t_v3	x;
	double	t;

	if (v3_dot(ray_dir, c.normal) == 0)
		return (INF);
	t = (v3_dot(c.normal, c.center) - v3_dot(origin, c.normal)) / \
v3_dot(ray_dir, c.normal);
	x = v3_add_vec(origin, v3_mult(ray_dir, t));
	if (v3_norm(v3_minus_vec(x, c.center)) > c.r)
		return (INF);
	if (rp.tmin <= t && t < rp.tmax)
		return (t);
	return (INF);
}

/** Returns the color of the circle at hitpoint.
 *
 * Explanation for the normal treatment: for flat surfaces like the circle and
 * the triangle we have a normal calculated or read during parsing. now it can
 * happen that this normal is not the one of the surface facing the camera. so
 * we need to select the one that is facing the cam in here. This is done by
 * calculating the dot product of the normal and the vector *from* the cam *to*
 * the hitpoint <tri.normal, cam2hit>. if dot-product < 0 this means the normal
 * is poiting towards the camera. then we take it. else flip it around 180deg.
 */
t_colr	circle_get_colr(t_scene scene, t_objlst cobj, t_v3 hit)
{
	t_circle	c;
	t_colr		colr_at_hitpoint;
	t_hp		hp;
	t_v3		cam2hit;

	cam2hit = v3_minus_vec(hit, scene.cam->pos);
	c = *(t_circle *)cobj.obj;
	hp.loc = hit;
	hp.cam2hp = v3_normalize(v3_minus_vec(scene.cam->pos, hit));
	hp.spec = c.spec;
	hp.scolr = c.colr;
	if (v3_dot(c.normal, cam2hit) < 0)
		hp.normal = c.normal;
	else
		hp.normal = v3_mult(c.normal, -1);
	colr_at_hitpoint = calculate_lights(scene, hp);
	return (colr_at_hitpoint);
}
