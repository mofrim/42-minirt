/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_colr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:44:27 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/11 12:06:13 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colr	calculate_lights(t_scene scene, t_v3 p, t_v3 n, t_colr obj_colr);
t_v3	get_normal_sphere(t_v3 hitpoint, t_v3 center);

/* Get the color of the found closest pixel. *This* is where all the future
 * magic will happen! */
t_colr	get_object_colr(t_scene scene, t_objlst *close_obj, t_v3 hitpoint)
{
	t_v3	normal_vec;

	if (close_obj == NULL)
		return ((t_colr){0, 0, 0});
	if (close_obj->type == SPHERE)
	{
		normal_vec = get_normal_sphere(hitpoint, ((t_sphere *)close_obj->obj)->center);
		return (calculate_lights(scene, hitpoint, normal_vec, ((t_sphere *)close_obj->obj)->colr));
	}
	return ((t_colr){0, 0, 0});
}

t_v3	get_normal_sphere(t_v3	hitpoint, t_v3 center)
{
	return (v3_get_norm(v3_add_vec(hitpoint, v3_mult(center, -1))));
}

t_colr	calculate_lights(t_scene scene, t_v3 hitpoint, t_v3 n, t_colr obj_colr)
{
	double		intens;
	double		ndotl;
	t_objlst	*objs;
	t_light		light;
	t_v3		light_ray;

	intens = scene.alight->ratio;
	objs = scene.objects;
	while (objs)
	{
		if (objs->type == LIGHT)
		{
			light = *(t_light *)objs->obj;
			// light_ray = v3_add_vec(hitpoint, v3_mult(light.pos, -1));
			light_ray = v3_add_vec(light.pos, v3_mult(hitpoint, -1));
			ndotl = v3_dot(n, light_ray);
			if (ndotl > 0)
				intens += light.bright * ndotl / \
						  (v3_norm(n) * v3_norm(light_ray));
		}
		objs = objs->next;
	}
	return (colr_mult(obj_colr, intens));
}
