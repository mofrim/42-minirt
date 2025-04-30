/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_xtra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:47:27 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/30 15:08:49 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Helper function to solve quadratic equation At^2 + Bt + C = 0
t_quad_sol	solve_quadratic(double a, double b, double c)
{
	t_quad_sol sol;

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
bool is_within_bounds(t_cylinder *cyl, t_v3 q)
{
	t_v3 q_minus_p1 = v3_minus_vec(q, cyl->p1);
	double proj = v3_dot(q_minus_p1, cyl->axis);
	// Check if projection onto axis is between 0 and height
	return (proj >= 0 && proj <= cyl->height);
	// Note: Using >= 0 and <= height includes hits exactly on the cap edges
	// Use > 0 and < height if caps are handled entirely separately.
	// The logic below assumes caps are handled separately, so use > and <.
	// return (proj > EPSILON && proj < cyl->height - EPSILON); // Using epsilon
}