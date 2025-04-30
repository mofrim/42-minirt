/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_at.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:21 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/30 16:58:28 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v3	get_normal_hp_sphere(t_v3 hp, t_v3 center);

/**
 * Get the normal vector at the hitpoint for the given obj.
 *
 * Select and return the value of the individual get_normal func for the obj's
 * type given as param.
 */
t_v3	get_normal_at_hp(t_objlst obj, t_v3 hploc)
{
	if (obj.type == SPHERE)
		return (get_normal_hp_sphere(hploc, ((t_sphere *)obj.obj)->center));
	if (obj.type == CIRCLE)
		return (((t_circle *)obj.obj)->normal);
	if (obj.type == TRIANGLE)
		return (((t_triangle *)obj.obj)->normal);
	else
		return (((t_plane *)obj.obj)->normal);
}

/* Returns the normal vector on the sphere at a given hitpoint. */
t_v3	get_normal_hp_sphere(t_v3 hp, t_v3 center)
{
	return (v3_normalize(v3_minus_vec(hp, center)));
}
