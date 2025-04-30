/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_lights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:01:17 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/30 17:42:03 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		calc_diff_reflection(t_light light, t_v3 light_ray, t_hp *hp);

/**
 * Calculate all light sources effect on the hipoint.
 *
 * Description: TODO
 */
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
				calc_diff_reflection(light, light_ray, &hp);
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
 *
 * About logic: we do the normal calculation in here bc... it's normis fault! it
 * is the 4 param limit :( otherwise it would make perfectly sense to pass the
 * normal to calculate light (as we had it befor) but, we also need the obj type
 * in here. this is due to the fact that we need to know if we are hitting a 2d
 * obj with our light ray. in this case there is no 'inside'. but there is still
 * a normal vector assigned to the obj. but for 2d objs it does not matter if
 * the dot product of the normal and the light_ray is negative. this is why we
 * take the fabs of it in that case. An explanatory example: with a circle and
 * its normal (0,-1,0)  a light-ray coming from (0,1,0) would not reflect on
 * this circle. This, we do not want!
 */
static int	calc_diff_reflection(t_light light, t_v3 light_ray, t_hp *hp)
{
	double	ndotl;
	double	ip;

	ndotl = v3_dot(hp->normal, light_ray);
	if (ndotl > 0)
	{
		ip = light.colr.i * ndotl / v3_norm(light_ray);
		light.colr.i = ip;
		hp->fcolr = hp_add_pointlight(*hp, light.colr);
		return (1);
	}
	return (0);
}
