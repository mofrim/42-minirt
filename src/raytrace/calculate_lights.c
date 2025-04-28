/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_lights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:01:17 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/28 22:27:10 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		calc_diff_reflection(t_light light, t_v3 light_ray, t_v3 n,
					t_hpcolr *hp);
static t_colr	get_colr_from_objlst(t_objlst obj);

/**
 * Calculate all light sources effect on the hipoint.
 *
 * Description: TODO
 */
t_colr	calculate_lights(t_scene scene, t_v3 hitpoint, t_v3 n, t_objlst obj)
{
	t_hpcolr	hp;
	t_objlst	*objs;
	t_light		light;
	t_v3		light_ray;

	hp.scolr = get_colr_from_objlst(obj);
	if (!scene.cam->is_inside_obj)
		hp.fcolr = hp_add_alight(hp.scolr, scene.alight->colr);
	else
		hp.fcolr = (t_colr){0, 0, 0, 0};
	objs = scene.objects;
	while (objs)
	{
		if (objs->type == LIGHT)
		{
			light = *(t_light *)objs->obj;
			light_ray = v3_minus_vec(light.pos, hitpoint);
			if (intersect_ray_objs(hitpoint, light_ray, \
				(t_ray_minmax){0.00000001, 0.99999999}, scene.objects).t == INF)
				calc_diff_reflection(light, light_ray, n, &hp);
		}
		objs = objs->next;
	}
	return (hp.fcolr);
}

/**
 * Calculate the diffuse reflection for a light source at a hitpoint.
 *
 * After long struggle this is what we have settled with for now... looks most
 * like PovRay. The main how-to-add-light-to-the-object logic is implemented in
 * hp_add_pointlight. In PovRay there is als the `falloff` parameter which leads
 * to the edges of the light area on an object being less fuzzy.
 */
static int	calc_diff_reflection(t_light light, t_v3 light_ray, t_v3 n,
		t_hpcolr *hp)
{
	double	ndotl;
	double	ip;

	ndotl = v3_dot(n, light_ray);
	if (ndotl > 0)
	{
		ip = light.colr.i * ndotl / v3_norm(light_ray);
		light.colr.i = ip;
		hp->fcolr = hp_add_pointlight(*hp, light.colr);
		return (1);
	}
	return (0);
}

t_colr	get_colr_from_objlst(t_objlst obj)
{
	if (obj.type == SPHERE)
		return (((t_sphere *)obj.obj)->colr);
	if (obj.type == PLANE)
		return (((t_plane *)obj.obj)->colr);
	if (obj.type == TRIANGLE)
		return (((t_triangle *)obj.obj)->colr);
	if (obj.type == CIRCLE)
		return (((t_circle *)obj.obj)->colr);
	if (obj.type == CYLINDER)
		return (((t_cylinder *)obj.obj)->colr);
	return ((t_colr){0, 0, 0, 0});
}
