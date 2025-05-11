/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:02:15 by zrz               #+#    #+#             */
/*   Updated: 2025/05/10 19:57:00 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Sets up the properties of a t_circle struct to represent one of the
** cylinder's caps. This allows reusing the `circle_intersect_ray` function.
** cap_idx: 0 for the bottom cap (related to cyl->p1), 1 for the top cap
** (related to cyl->p2). The normal vector is set to point outwards from
** the cylinder.
*/
static void	setup_cap_as_circle(\
	t_circle *cap_circle, t_cyl_intersect_params *params, int cap_idx)
{
	cap_circle->r = params->cyl->r;
	cap_circle->r2 = params->cyl->r_squared;
	cap_circle->colr = params->cyl->colr;
	if (cap_idx == 0)
	{
		cap_circle->center = params->cyl->p1;
		cap_circle->normal = v3_mult(params->cyl->axis, -1.0);
	}
	else
	{
		cap_circle->center = params->cyl->p2;
		cap_circle->normal = params->cyl->axis;
	}
}

/*
** Intersects the ray with both circular caps of the cylinder.
** It configures two t_circle structures, one for each cap, and then calls
** `circle_intersect_ray` for each. It returns the smallest valid 't' value
** from these two potential intersections. If neither cap is hit within the
** valid ray range (rp.tmin, rp.tmax), it returns INF.
*/
double	intersect_caps_circles(t_cyl_intersect_params *params)
{
	t_circle	cap_circle_bottom;
	t_circle	cap_circle_top;
	double		t_hit_bottom;
	double		t_hit_top;
	double		closest_t_cap;

	setup_cap_as_circle(&cap_circle_bottom, params, 0);
	t_hit_bottom = circle_intersect_ray(params->origin, params->ray_dir, \
params->rp, cap_circle_bottom);
	setup_cap_as_circle(&cap_circle_top, params, 1);
	t_hit_top = circle_intersect_ray(params->origin, params->ray_dir, \
params->rp, cap_circle_top);
	closest_t_cap = INF;
	if (t_hit_bottom > params->rp.tmin && t_hit_bottom < params->rp.tmax)
		closest_t_cap = t_hit_bottom;
	if (t_hit_top > params->rp.tmin && t_hit_top < params->rp.tmax)
		if (t_hit_top < closest_t_cap)
			closest_t_cap = t_hit_top;
	return (closest_t_cap);
}
