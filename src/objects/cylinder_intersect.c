/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:15:36 by zrz               #+#    #+#             */
/*   Updated: 2025/08/17 17:27:27 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Calculates the closest intersection point of a ray with the cylinder's body.
 * It prepares parameters and calls helper functions to determine if and where
 * the ray intersects the infinite cylinder's curved surface, then checks if
 * that intersection point lies within the finite height of the cylinder.
 */
static double	intersect_cylinder_body_main(t_cyl_intersect_params *params)
{
	double	t_body_hit;

	t_body_hit = calculate_body_intersection_t(params);
	return (t_body_hit);
}

/**
 * Intersects the ray with both circular caps of the cylinder.
 * It configures two t_circle structures, one for each cap, and then calls
 * `circle_intersect_ray` for each. It returns the smallest valid 't' value
 * from these two potential intersections. If neither cap is hit within the
 * valid ray range (rp.tmin, rp.tmax), it returns INF.
 */
static double	intersect_caps_circles(t_cyl_intersect_params *params)
{
	double		t_hit_bottom;
	double		t_hit_top;
	double		closest_t_cap;

	t_hit_bottom = circle_intersect_ray(params->origin, params->ray_dir, \
params->rp, &params->cyl->cap2);
	t_hit_top = circle_intersect_ray(params->origin, params->ray_dir, \
params->rp, &params->cyl->cap1);
	closest_t_cap = INF;
	if (t_hit_bottom > params->rp.tmin && t_hit_bottom < params->rp.tmax)
		closest_t_cap = t_hit_bottom;
	if (t_hit_top > params->rp.tmin && t_hit_top < params->rp.tmax)
		if (t_hit_top < closest_t_cap)
			closest_t_cap = t_hit_top;
	return (closest_t_cap);
}

/*
** Calculates the closest intersection point of a ray with the cylinder's caps.
** It treats each cap as a circle and uses the `intersect_caps_circles`
** utility function to find the nearest valid intersection.
*/
static double	intersect_cylinder_caps_main(t_cyl_intersect_params *params)
{
	double	t_caps_hit;

	t_caps_hit = intersect_caps_circles(params);
	return (t_caps_hit);
}

/*
** Selects the closest valid intersection distance from the body and cap hits.
** It ensures that the chosen 't' value is positive and within the ray's
** defined t_min and t_max range. If both are invalid or INF, INF is returned.
*/
static double	select_closest_valid_t(double t_body, double t_caps, \
t_ray_minmax rp)
{
	double	closest_t;

	closest_t = INF;
	if (t_body > rp.tmin && t_body < rp.tmax)
	{
		closest_t = t_body;
	}
	if (t_caps > rp.tmin && t_caps < rp.tmax)
	{
		if (t_caps < closest_t)
		{
			closest_t = t_caps;
		}
	}
	return (closest_t);
}

/*
** Determines the closest intersection point of a ray with a finite cylinder.
** This function checks for intersections with both the cylinder's curved body
** and its two circular end caps. It initializes parameters for intersection
** calculations and then calls helper functions to find intersections with the
** body and caps. Finally, it returns the smallest positive 't' value
** (distance) to a valid intersection, or INF if no intersection occurs.
*/
double	cylinder_intersect_ray(
	t_v3 origin,
	t_v3 ray_dir,
	t_ray_minmax rp,
	t_cylinder *cyl)
{
	t_cyl_intersect_params	params;
	double					t_body_hit;
	double					t_caps_hit;
	double					t_final;

	params.origin = origin;
	params.ray_dir = ray_dir;
	params.cyl = cyl;
	params.rp = rp;
	t_body_hit = intersect_cylinder_body_main(&params);
	t_caps_hit = intersect_cylinder_caps_main(&params);
	t_final = select_closest_valid_t(t_body_hit, t_caps_hit, rp);
	return (t_final);
}
