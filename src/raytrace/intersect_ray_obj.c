/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:29:10 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/10 23:46:06 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Generalized ray obj intersection function. Dispatches to the specific object
 * type intersection function. */
double 	intersect_ray_obj(t_v3 cam_pos, t_v3 ray_dir, t_objlst *obj)
{
	if (obj->type == SPHERE)
		return (intersect_ray_sphere(cam_pos, ray_dir, obj->obj));
	return (0);
}
