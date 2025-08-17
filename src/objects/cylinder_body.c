/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_body.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:17:17 by zrz               #+#    #+#             */
/*   Updated: 2025/08/17 17:30:14 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_quad_sol	solve_quadratic(double a, double b, double c);
bool				is_within_bounds(t_cylinder *cyl, t_v3 q);

/**
 * Calculates the coefficients (a, b, c) of the quadratic equation used to find
 * intersections with an infinite cylinder's body.
 * co: vector from ray origin to cylinder's base point (p1).
 * dot_rd_axis: dot product of ray direction and cylinder axis.
 * dot_co_axis: dot product of co and cylinder axis.
 */
static void	calculate_body_quadratic_coeffs(
	t_cyl_intersect_params *params, t_quad_coeffs *coeffs)
{
	t_v3	co;
	double	dot_rd_axis;
	double	dot_co_axis;
	double	r_sq;

	co = v3_minus_v3(params->origin, params->cyl->p1);
	dot_rd_axis = v3_dot(params->ray_dir, params->cyl->axis);
	dot_co_axis = v3_dot(co, params->cyl->axis);
	r_sq = params->cyl->r_squared;
	coeffs->a = v3_dot(params->ray_dir, params->ray_dir) - \
(dot_rd_axis * dot_rd_axis);
	coeffs->b = 2.0 * (v3_dot(params->ray_dir, co) - \
(dot_rd_axis * dot_co_axis));
	coeffs->c = v3_dot(co, co) - (dot_co_axis * dot_co_axis) - r_sq;
}

/**
 * Solves the quadratic equation for cylinder body intersection and finds the
 * smallest valid 't' (distance).
 * It iterates through the two potential solutions (t1, t2) from the
 * quadratic formula. For each 't', it checks if it's within the ray's
 * valid range (rp.tmin, rp.tmax). If so, it calculates the intersection point
 * and verifies if this point lies on the finite segment of the cylinder body
 * using `is_within_bounds`.
 */
static double	solve_and_get_valid_t_body(\
	t_cyl_intersect_params *params, t_quad_coeffs *coeffs)
{
	t_quad_sol	sol;
	double		t_hits[2];
	double		closest_t;
	int			i;
	t_v3		hit_point;

	sol = solve_quadratic(coeffs->a, coeffs->b, coeffs->c);
	closest_t = INF;
	if (sol.disc < 0)
		return (INF);
	t_hits[0] = sol.t1;
	t_hits[1] = sol.t2;
	i = 0;
	while (i < 2)
	{
		if (t_hits[i] > params->rp.tmin && t_hits[i] < params->rp.tmax)
		{
			hit_point = v3_add_v3(params->origin, \
v3_mult(params->ray_dir, t_hits[i]));
			if (is_within_bounds(params->cyl, hit_point))
				if (t_hits[i] < closest_t)
					closest_t = t_hits[i];
		}
		i++;
	}
	return (closest_t);
}

/**
 * Calculates the 't' value for the intersection with the cylinder's body.
 * It first computes the coefficients of the quadratic equation. If 'a' is
 * near zero, the ray is parallel to the cylinder axis, and no intersection
 * with the curved body is possible (or it's a grazing hit, treated as miss).
 * Otherwise, it solves the quadratic equation and validates the intersection
 * points against the cylinder's finite height and ray's t_min/t_max.
 */
double	calculate_body_intersection_t(t_cyl_intersect_params *params)
{
	t_quad_coeffs	coeffs;
	double			t_hit;

	calculate_body_quadratic_coeffs(params, &coeffs);
	if (fabs(coeffs.a) < EPS)
	{
		return (INF);
	}
	t_hit = solve_and_get_valid_t_body(params, &coeffs);
	return (t_hit);
}

// Helper function to solve quadratic equation At^2 + Bt + C = 0
t_quad_sol	solve_quadratic(double a, double b, double c)
{
	t_quad_sol	sol;

	sol.disc = b * b - 4 * a * c;
	if (sol.disc < 0)
	{
		sol.t1 = INF;
		sol.t2 = INF;
	}
	else
	{
		sol.t1 = (-b + sqrt(sol.disc)) / (2 * a);
		sol.t2 = (-b - sqrt(sol.disc)) / (2 * a);
	}
	return (sol);
}

// Check if intersection point q is within the cylinder height bounds
bool	is_within_bounds(t_cylinder *cyl, t_v3 q)
{
	t_v3	q_minus_p1;
	double	proj;

	q_minus_p1 = v3_minus_v3(q, cyl->p1);
	proj = v3_dot(q_minus_p1, cyl->axis);
	return (proj >= 0 && proj <= cyl->height);
}
