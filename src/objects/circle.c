/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:22:32 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/29 14:54:19 by fmaurer          ###   ########.fr       */
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

/* Returns the color of the sphere at the hitpoint. So far only for ambient and
 * diffuse lighting. */
t_colr	circle_get_colr(t_scene scene, t_objlst cobj, t_v3 hitpoint)
{
	t_circle	c;
	t_colr		colr_at_hitpoint;
	t_hp		hp;

	c = *(t_circle *)cobj.obj;
	hp.loc = hitpoint;
	hp.scolr = c.colr;
	colr_at_hitpoint = calculate_lights(scene, hp, cobj);
	return (colr_at_hitpoint);
}
