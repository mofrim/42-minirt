/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_colr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:16:01 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/02 15:29:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Returns the color of the sphere at the hitpoint. So far only for ambient and
 * diffuse lighting. */
t_colr	circle_get_colr(t_scene scene, t_circle c, t_v3 hitpoint)
{
	t_v3	normal_vec;
	t_colr	colr_at_hitpoint;

	normal_vec = v3_get_norm(c.normal);
	colr_at_hitpoint = calculate_lights(scene, hitpoint, normal_vec, c.colr);
	return (colr_at_hitpoint);
}
