/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:27:23 by zrz               #+#    #+#             */
/*   Updated: 2025/08/17 17:29:37 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Checks if the hit point lies on the surface of a specific cylinder cap.
 * params: Contains cylinder data and the hit point.
 * cap_select: 0 for the bottom cap (centered at p1), 1 for the top cap (p2).
 * Returns: 1 if the hit point is on the specified cap surface, 0 otherwise.
 * A point is on the cap surface if it's on the cap's plane and within its
 * radius.
 */
static int	is_on_cap_surface_internal(
		t_cyl_normal_params *params,
		int cap_select)
{
	t_v3	cap_center;
	t_v3	vec_to_hit;
	double	dist_to_plane;
	double	dist_from_center_sq;

	if (cap_select == 0)
		cap_center = params->cyl->p1;
	else
		cap_center = params->cyl->p2;
	vec_to_hit = v3_minus_v3(params->hit_point, cap_center);
	dist_to_plane = v3_dot(vec_to_hit, params->cyl->axis);
	if (fabs(dist_to_plane) < EPS)
	{
		dist_from_center_sq = v3_dot(vec_to_hit, vec_to_hit);
		if (dist_from_center_sq <= params->cyl->r_squared + EPS)
			return (1);
	}
	return (0);
}

/**
 * Computes the geometric normal vector for a point on the cylinder's body.
 * params: Contains cylinder data (p1, axis) and the hit_point.
 * The normal is perpendicular to the cylinder's axis and points outwards
 * from the hit point.
 */
static t_v3	get_body_normal_geometric(t_cyl_normal_params *params)
{
	t_v3	cp_vec;
	double	projection_len;
	t_v3	point_on_axis;
	t_v3	normal;

	cp_vec = v3_minus_v3(params->hit_point, params->cyl->p1);
	projection_len = v3_dot(cp_vec, params->cyl->axis);
	point_on_axis = v3_add_v3(params->cyl->p1, \
v3_mult(params->cyl->axis, projection_len));
	normal = v3_minus_v3(params->hit_point, point_on_axis);
	normal = v3_normalize(normal);
	return (normal);
}

/**
 * Retrieves the geometric normal vector for a specific cylinder cap.
 * params: Contains cylinder data (axis).
 * cap_select: 0 for the bottom cap (normal is -axis),
 * 1 for top (normal is axis).
 */
static t_v3	get_cap_normal_geometric(t_cyl_normal_params *params, \
int cap_select)
{
	t_v3	normal;

	if (cap_select == 0)
	{
		normal = v3_mult(params->cyl->axis, -1.0);
	}
	else
	{
		normal = params->cyl->axis;
	}
	return (normal);
}

/**
 * Calculates the surface normal of the cylinder at a given hit point.
 * params: A pointer to t_cyl_normal_params containing the cylinder, hit point,
 * and incident ray direction.
 * This function determines if the hit is on a cap or the body, calculates the
 * geometric normal, and then orients this normal to face the incident ray.
 * The incident_ray_dir in params is used for correct orientation.
 */
t_v3	calculate_cylinder_normal_at_hit(t_cyl_normal_params *params)
{
	t_v3	geometric_normal;

	if (is_on_cap_surface_internal(params, 0))
		geometric_normal = get_cap_normal_geometric(params, 0);
	else if (is_on_cap_surface_internal(params, 1))
		geometric_normal = get_cap_normal_geometric(params, 1);
	else
		geometric_normal = get_body_normal_geometric(params);
	if (v3_dot(params->incident_ray_dir, geometric_normal) > 0.0)
		geometric_normal = v3_mult(geometric_normal, -1.0);
	return (geometric_normal);
}
