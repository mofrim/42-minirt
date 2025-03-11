/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:33:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/11 12:11:26 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* The intersection of the ray with the object. The heart of raytracing. */
// QUESTION: is returning the smaller of both solutions a good approach? It
// might also be possible that one of them is smaller than 0, thus it it is
// invalid and the other, even though it is greater, is the correct one!
// ANSWER: mitigated this for now by checking inside of this function, but maybe
// it have to think about this more later....
double	intersect_ray_sphere(t_v3 cam_pos, t_v3 ray_dir, t_sphere *sphere)
{
	t_v2	res;
	t_v3	co;
	t_v3	abc;
	double	disc;

	co = v3_add_vec(cam_pos, v3_mult(sphere->center, -1));
	abc.x = v3_dot(ray_dir, ray_dir);
	abc.y = 2 * v3_dot(co, ray_dir);
	abc.z = v3_dot(co, co) - sphere->r_squared;
	disc = abc.y * abc.y - 4 * abc.x * abc.z;
	if (disc < 0)
		return (INF);
	res.x1 = (-abc.y + sqrt(disc)) / (2 * abc.x);
	res.x2 = (-abc.y - sqrt(disc)) / (2 * abc.x);
	if (VIEWZ < res.x1 && res.x1 < INF && res.x1 < res.x2)
		return (res.x1);
	if (VIEWZ < res.x2 && res.x2 < INF)
		return (res.x2);
	return (0);
}
