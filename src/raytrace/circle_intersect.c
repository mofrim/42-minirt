/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:22:32 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/03 10:37:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * The Circle-Ray intersection calculation.
 *
 * 		<(O + t * R - C), n> = 0
 *
 * with <x,y> = scalar product, O = origin, R = ray_dir, C = center of circle, n
 * = circle normal is to be solved.
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
	if (v3_norm(v3_add_vec(x, v3_mult(c.center, -1))) > c.r)
		return (INF);
	if (rp.tmin <= t && t < rp.tmax)
	{
		printf("t = %lf\n", t);
		return (t);
	}
	return (INF);
}
