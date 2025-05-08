/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:33:53 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 10:03:34 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Make a new t_v3 from the x,y,z coords. Allocates and returns a pointer to
 * that mem. */
t_v3	*v3_new_alloc(double x, double y, double z)
{
	t_v3	*p;

	p = malloc(sizeof(t_vec3));
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

/* Make a new t_v3 *without* allocation. For use in direct assignments. */
t_v3	v3_new(double x, double y, double z)
{
	t_v3	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

/* Print a t_v3 and its name. */
void	v3_print(t_v3 v, char *name)
{
	printf("v3-%s: (%f, %f, %f)\n", name, v.x, v.y, v.z);
}
