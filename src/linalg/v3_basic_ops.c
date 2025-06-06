/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_basic_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:33:53 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 22:52:23 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Add a scalar to each component of a t_v3. Returns result. */
t_v3	v3_add_scalar(t_v3 v, double d)
{
	v.x += d;
	v.y += d;
	v.z += d;
	return (v);
}

/* Add 2 t_v3's component-wise. Returns result. */
t_v3	v3_add_v3(t_v3 v, t_v3 w)
{
	v.x += w.x;
	v.y += w.y;
	v.z += w.z;
	return (v);
}

/* Substract to v3's. */
t_v3	v3_minus_v3(t_v3 v, t_v3 w)
{
	v.x -= w.x;
	v.y -= w.y;
	v.z -= w.z;
	return (v);
}

/* Multiply each component by a double scalar. Returns result. */
t_v3	v3_mult(t_v3 v, double d)
{
	v.x *= d;
	v.y *= d;
	v.z *= d;
	return (v);
}

/* Print a t_v3 and its name. */
void	v3_print(t_v3 v, char *name)
{
	printf("v3-%s: (%f, %f, %f)\n", name, v.x, v.y, v.z);
}
