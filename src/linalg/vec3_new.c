/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:33:53 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 10:04:38 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * t_vec3 vs. t_v3
 *
 * So... we do not know yet what kind of vector will be most handy with this
 * project. So far it feels like f.ex. for saving the camera position inside the
 * t_camera struct a t_v3 is sufficient and uses a lot less memory than a
 * t_vec3. If we than were to do calculations, we can assign locally (on the
 * stack) inside a function where we do calculations the t_v3 to a t_vec3 and do
 * the calculations with this.
 */

t_vec3	*vec3_new_alloc(double x, double y, double z)
{
	t_vec3	*p;

	p = malloc(sizeof(t_vec3));
	p->x = x;
	p->y = y;
	p->z = z;
	p->add_scalar = add_scalar;
	p->add_vec = add_vec;
	p->add_vec_coords = add_vec_coords;
	p->mult = mult;
	p->dot = dot;
	p->cross = cross;
	return (p);
}

/* Make a new t_vec3 vector from xyz coords *without* allocation. For use in
 * direct assignments etc. */
t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3	p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.add_scalar = add_scalar;
	p.add_vec = add_vec;
	p.add_vec_coords = add_vec_coords;
	p.mult = mult;
	p.dot = dot;
	p.cross = cross;
	return (p);
}

/* Make a new t_vec3 from a t_v3 without allocation! */
t_vec3	vec3_new_v3(t_v3 v)
{
	t_vec3	p;

	p.x = v.x;
	p.y = v.y;
	p.z = v.z;
	p.add_scalar = add_scalar;
	p.add_vec = add_vec;
	p.add_vec_coords = add_vec_coords;
	p.mult = mult;
	p.dot = dot;
	p.cross = cross;
	return (p);
}
