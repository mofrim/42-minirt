/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:25:49 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/30 15:15:33 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Intersect with the two cap planes and check if inside radiusZ
static double intersect_caps(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp, t_cylinder *cyl)
{
	double	t_cap1;
	double	t_cap2;
	double denom;
	t_v3 hit_p;

	t_cap1 = INF;
	t_cap2 = INF;
	denom = v3_dot(ray_dir, cyl->axis);
	if (fabs(denom) > EPSILON)
	{
		t_cap1 = v3_dot(v3_minus_vec(cyl->p1, origin), cyl->axis) / denom;
		if (rp.tmin < t_cap1 && t_cap1 < rp.tmax)
		{
			hit_p = v3_add_vec(origin, v3_mult(ray_dir, t_cap1));
			if (v3_norm_sq(v3_minus_vec(hit_p, cyl->p1)) > cyl->r_squared)
				t_cap1 = INF;
		}
		else
			t_cap1 = INF;
		t_cap2 = v3_dot(v3_minus_vec(cyl->p2, origin), cyl->axis) / denom;
		if (rp.tmin < t_cap2 && t_cap2 < rp.tmax)
		{
			hit_p = v3_add_vec(origin, v3_mult(ray_dir, t_cap2));
			if (v3_norm_sq(v3_minus_vec(hit_p, cyl->p2)) > cyl->r_squared)
				t_cap2 = INF;
		}
		else
			t_cap2 = INF;
	}
	return fmin(t_cap1, t_cap2);
}

// Main cylinder intersection function
// Use p1 as the reference point pa from the PDF formula
// Calculate terms needed for quadratic coefficients
// v_perp = ray_dir - dot(ray_dir, cyl->axis) * cyl->axis;
// dp_perp = delta_p - dot(delta_p, cyl->axis) * cyl->axis;
// c = v3_norm_sq(dp_perp) - cyl->r_squared
// Check if ray origin is inside the infinite cylinder

double cylinder_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp, t_cylinder *cyl)
{
	t_v3 delta_p;
	t_v3 v_perp, dp_perp;
	double a, b, c;
	t_quad_sol body_sol;
	double t_body = INF, t_caps = INF;
	t_v3 hit_p1, hit_p2;

	delta_p = v3_minus_vec(origin, cyl->p1);
	v_perp = v3_minus_vec(ray_dir, v3_mult(cyl->axis, v3_dot(ray_dir, cyl->axis)));
	dp_perp = v3_minus_vec(delta_p, v3_mult(cyl->axis, v3_dot(delta_p, cyl->axis)));
	a = v3_dot(v_perp, v_perp);
	b = 2 * v3_dot(v_perp, dp_perp);
	c = v3_dot(dp_perp, dp_perp) - cyl->r_squared;
	if (fabs(a) < EPSILON)
	{
		 if (c > 0) return INF;
		 return intersect_caps(origin, ray_dir, rp, cyl);
	}

	body_sol = solve_quadratic(a, b, c);
	
	if (body_sol.disc < 0)
	{
		return intersect_caps(origin, ray_dir, rp, cyl);
	}
	if (rp.tmin < body_sol.t1 && body_sol.t1 < rp.tmax)
	{
		hit_p1 = v3_add_vec(origin, v3_mult(ray_dir, body_sol.t1));
		if (is_within_bounds(cyl, hit_p1))
			t_body = body_sol.t1;
	}
	if (rp.tmin < body_sol.t2 && body_sol.t2 < rp.tmax)
	{
		 hit_p2 = v3_add_vec(origin, v3_mult(ray_dir, body_sol.t2));
		 if (is_within_bounds(cyl, hit_p2))
		 {
			 if (t_body == INF || body_sol.t2 < t_body)
				 t_body = body_sol.t2;
		 }
	}
	t_caps = intersect_caps(origin, ray_dir, rp, cyl);
	return fmin(t_body, t_caps);
}

t_colr	cylinder_get_colr(t_scene scene, t_objlst cylobj, t_v3 hitpoint)
{
	t_cylinder *cyl;
	t_v3 normal_vec;
	t_v3 p_axis;
	double m;
	double dist_to_p1_plane;
	double dist_to_p2_plane;

	cyl = (t_cylinder *)cylobj.obj;
	m = v3_dot(v3_minus_vec(hitpoint, cyl->p1), cyl->axis);
	dist_to_p1_plane = m;
	dist_to_p2_plane = cyl->height - m;
	if (dist_to_p1_plane < EPSILON)
		normal_vec = v3_mult(cyl->axis, -1.0);
	else if (dist_to_p2_plane < EPSILON)
		normal_vec = cyl->axis;
	else
	{
		p_axis = v3_add_vec(cyl->p1, v3_mult(cyl->axis, m));
		normal_vec = v3_get_norm(v3_minus_vec(hitpoint, p_axis));
	}
	return (calculate_lights(scene, hitpoint, normal_vec, cylobj));
}
