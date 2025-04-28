/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_colr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:44:27 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/28 14:56:56 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Get the color of the intersection point. *This* is where all the future
 * magic will happen! */
t_colr	get_object_colr(t_scene scene, t_objlst *close_obj, t_v3 hitpoint)
{
	if (close_obj == NULL)
		return ((t_colr){0, 0, 0, 0.5});
	else if (close_obj->type == SPHERE)
		return (sphere_get_colr(scene, *close_obj, hitpoint));
	else if (close_obj->type == CIRCLE)
		return (circle_get_colr(scene, *close_obj, hitpoint));
	else if (close_obj->type == TRIANGLE)
		return (triangle_get_colr(scene, *close_obj, hitpoint));
	else if (close_obj->type == CYLINDER)
        return (cylinder_get_colr(scene, *close_obj, hitpoint));
    // else if (close_obj->type == PLANE)
        // return (plane_get_colr(scene, *close_obj, hitpoint));
	return ((t_colr){0, 0, 0, 0.5});
}
