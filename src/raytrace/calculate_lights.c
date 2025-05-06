/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_lights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:01:17 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/06 20:56:19 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		calc_reflections(t_light light, t_v3 light_ray, t_hp *hp);

/**
 * Calculate all light sources effect on the hipoint.
 *
 * Description: TODO
 */
// QUESTION why starts the light_ray from the hitpoint?!
t_colr	calculate_lights(t_scene scene, t_hp hp)
{
	t_objlst	*objs;
	t_light		light;
	t_v3		light_ray;

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
			light_ray = v3_minus_vec(light.pos, hp.loc);
			if (intersect_ray_objs(hp.loc, light_ray, \
				(t_ray_minmax){0.00000001, 0.99999999}, scene.objects).t == INF)
				calc_reflections(light, light_ray, &hp);
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
static void	calc_reflections(t_light light, t_v3 light_ray, t_hp *hp)
{
	double	ndotl;
	double	rdotcam2hp;
	double	ip;
	t_v3	refl;

	ip = 0;
	ndotl = v3_dot(hp->normal, light_ray);
	if (ndotl > 0)
		ip += light.colr.i * ndotl / v3_norm(light_ray);
	if (hp->spec > 0)
	{
		refl = v3_minus_vec(v3_mult(hp->normal, 2 * ndotl), light_ray);
		rdotcam2hp = v3_dot(refl, hp->cam2hp);
		if (rdotcam2hp > 0)
			ip += light.colr.i * pow(rdotcam2hp / v3_norm(refl), hp->spec);
	}
	light.colr.i = ip;
	hp->fcolr = hp_add_pointlight(*hp, light.colr);
}
