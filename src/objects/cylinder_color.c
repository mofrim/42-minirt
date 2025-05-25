/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:28:23 by zrz               #+#    #+#             */
/*   Updated: 2025/05/25 18:59:08 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Sets up the parameters required for calculating the cylinder's surface normal.
** norm_p: Pointer to the t_cyl_normal_params struct to be initialized.
** scene: The main scene struct, used to get camera position for incident ray.
** cylobj: The object list item for the cylinder, to access cylinder data.
** hitpoint: The 3D coordinates of the intersection point on the cylinder.
** The incident_ray_dir is calculated from the camera to the hitpoint.
** is_cap_hit and cap_normal_idx are not set here; they are determined by
** the normal calculation function itself.
*/
static void	setup_normal_params(
	t_cyl_normal_params *norm_p,
	t_scene scene,
	t_objlst cylobj,
	t_v3 hitpoint)
{
	norm_p->cyl = (t_cylinder *)cylobj.obj;
	norm_p->hit_point = hitpoint;
	norm_p->incident_ray_dir = v3_normalize(v3_minus_v3(hitpoint,
				scene.cam->pos));
	norm_p->is_cap_hit = 0;
	norm_p->cap_normal_idx = 0;
}

/*
** Calculates the color of the cylinder at a given intersection point.
** scene: The scene data, including lights and camera.
** cylobj: The object list item representing the hit cylinder.
** hitpoint: The 3D coordinates of the intersection point on the cylinder.
** This function first sets up parameters for normal calculation, then calls
** `calculate_cylinder_normal_at_hit` to get the surface normal. Finally, it
** uses this normal and other scene information to compute the lighting and
** determine the color at the hit point via `calculate_lights`.
*/
t_colr	cylinder_get_colr(t_scene scene, t_objlst cylobj, t_v3 hit)
{
	t_cylinder			c;
	t_cyl_normal_params	normal_params;
	t_colr				final_color;
	t_hp				hp;

	c = *(t_cylinder *)cylobj.obj;
	hp.loc = hit;
	hp.cam2hp = v3_normalize(v3_minus_v3(scene.cam->pos, hit));
	hp.scolr = c.colr;
	hp.spec = c.spec;
	setup_normal_params(&normal_params, scene, cylobj, hit);
	hp.normal = calculate_cylinder_normal_at_hit(&normal_params);
	final_color = calculate_lights(scene, hp);
	return (final_color);
}
