/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_get_normal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:45:26 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/15 10:29:45 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_v3	colr_to_normal(t_colr ncolr);
t_v3		get_tangent_space_normal(t_v3 nmap_normal, t_v3 sphere_normal);

/* Returns the normal vector on the sphere at a given hitpoint. */
t_v3	sphere_get_normal(t_v3	hp, t_sphere s)
{
	double			u;
	double			v;
	unsigned char	*colr_addr;
	t_v3			normal;
	t_img			*img;

	if (s.bump && s.tex_img)
		return (sphere_bump(hp, s));
	if (!s.nmap_img)
		return (v3_normalize(v3_minus_vec(hp, s.center)));
	img = s.nmap_img;
	hp = v3_normalize(v3_minus_vec(hp, s.center));
	u = (atan2(hp.z, hp.x) + M_PI) / (2 * M_PI);
	v = acos(hp.y) / M_PI;
	colr_addr = (unsigned char *)&img->data[(int)(img->height * v) * \
img->size_line + (int)(img->width * u) * img->bpp / 8];
	normal = colr_to_normal(
			int_to_tcolr(get_intcolr_from_data(colr_addr, img->bpp / 8)));
	normal = get_tangent_space_normal(normal, hp);
	return (normal);
}

static t_v3	colr_to_normal(t_colr ncolr)
{
	t_v3	n;

	n.x = 2.0 * ncolr.r / 255.0f - 1.0;
	n.y = 2.0 * ncolr.g / 255.0f - 1.0;
	n.z = 2.0 * ncolr.b / 255.0f - 1.0;
	return (v3_normalize(n));
}

/* Simpler version avoiding trigo functions but still producing a valid tangent.
 * Should also work. The idea is that the cross prod with any vector not
 * parallel to the normal, will be in tangent space. That's it. */
t_v3	sphere_get_tangent(t_v3 sphere_normal)
{
	t_v3	vec;

	if (fabs(sphere_normal.y) < 0.99)
		vec = (t_v3){0, 1, 0};
	else
		vec = (t_v3){1, 0, 0};
	return (v3_normalize(v3_cross(vec, sphere_normal)));
}

t_v3	get_tangent_space_normal(t_v3 nmap_normal, t_v3 sphere_normal)
{
	t_v3	tangent;
	t_v3	binormal;
	t_v3	tnormal;

	tangent = v3_normalize(sphere_get_tangent(sphere_normal));
	binormal = v3_normalize(v3_cross(sphere_normal, tangent));
	tangent = v3_mult(tangent, nmap_normal.x);
	binormal = v3_mult(binormal, nmap_normal.y);
	tnormal = v3_mult(sphere_normal, nmap_normal.z);
	return (v3_normalize(v3_add_vec(tangent, v3_add_vec(binormal, tnormal))));
}

/* A first version of the get tangent function. Somehow this produced glitches,
 * i.e. spots where somehting weird was happening. */

// t_v3	get_tangent(double u, double v)
// {
// 	double	theta;
// 	double	phi;
// 	t_v3	dtheta;
//
// 	theta = 2 * M_PI * u;
// 	phi = M_PI * v;
// 	dtheta.x = -sin(phi) * sin(theta);
// 	dtheta.y = sin(phi) * cos(theta);
// 	dtheta.z = 0;
// 	// dtheta.z = -sin(phi) * cos(theta);
// 	// dtheta.y = 0;
// 	return (v3_normalize(dtheta));
// }
