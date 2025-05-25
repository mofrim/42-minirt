/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_get_colr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:39:50 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 18:59:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colr	hyper_get_scolr(t_hyper h, t_v3 hp);
t_colr	hyper_get_checker_colr(t_hyper h, t_v3 hp);
t_colr	hyper_get_tex_colr(t_hyper h, t_v3 hp);

/* Ahh, we couuuld generalize this function for all shapes... but, no. */
t_colr	hyper_get_colr(t_scene scene, t_objlst hobj, t_v3 hit)
{
	t_hyper	h;
	t_colr	colr_at_hitpoint;
	t_hp	hp;

	h = *(t_hyper *)hobj.obj;
	hp.loc = hit;
	hp.cam2hp = v3_normalize(v3_minus_v3(scene.cam->pos, hit));
	hp.scolr = hyper_get_scolr(h, hp.loc);
	hp.spec = h.spec;
	hp.normal = hyper_get_normal(hp.loc, h);
	colr_at_hitpoint = calculate_lights(scene, hp);
	return (colr_at_hitpoint);
}

/* Get the surface color for the hyper. */
t_colr	hyper_get_scolr(t_hyper h, t_v3 hp)
{
	if (!h.tex_img && !h.checker)
		return (h.colr);
	if (h.checker)
		return (hyper_get_checker_colr(h, hp));
	return (hyper_get_tex_colr(h, hp));
}

/**
 * The hyper u/v transform.
 *
 * Using the parametric representation x = a * cosh(v) * cos(t), y = b * cosh(v)
 * * sin(t), z = c * sinh(t), the u/v mapping is calculated.
 */
t_uv	hyper_get_uv(t_hyper h, t_v3 hp)
{
	t_uv	res;
	double	vmin;
	double	vmax;
	double	r_xz;

	if (h.checker == 1 || h.checker == 0)
		hp = v3_minus_v3(hp, h.center);
	if (h.checker == 2 || h.checker == 3)
		hp = v3_normalize(v3_minus_v3(hp, h.center));
	res.u = atan2(hp.z / h.ab, hp.x / h.ab) + M_PI;
	if (h.checker == 3)
		res.u = atan2(hp.y / h.ab, hp.x / h.ab) + M_PI;
	r_xz = fmax((1 / h.ab * sqrt((hp.x * hp.x) + (hp.z * hp.z))), 1.0);
	res.v = acosh(r_xz);
	if (hp.y < 0)
		res.v = -res.v;
	res.u /= 2 * M_PI;
	vmin = asinh(h.hby2 / h.c);
	vmax = asinh(-h.hby2 / h.c);
	res.v = (res.v - vmin) / (vmax - vmin);
	res.u = fmod(res.u, 1.0);
	if (res.u < 0)
		res.u += 1.0;
	res.v = fmax(0.0, fmin(1.0, res.v));
	return (res);
}

/* Return checker pattern color. */
t_colr	hyper_get_checker_colr(t_hyper h, t_v3 hp)
{
	t_uv	uv;
	int		checker_u;
	int		checker_v;

	uv = hyper_get_uv(h, hp);
	checker_u = floor(h.checker_scale * uv.u + EPS);
	checker_v = floor(h.checker_scale * uv.v + EPS);
	if (((checker_u + checker_v) % 2) == 0)
		return (colr_get_darker(h.colr));
	return (colr_get_brightest(h.colr));
}

/* Map the texture onto the hyper. */
t_colr	hyper_get_tex_colr(t_hyper h, t_v3 hp)
{
	t_uv			uv;
	t_colr			texel;
	unsigned char	*colr_addr;
	t_img			*img;

	img = h.tex_img;
	uv = hyper_get_uv(h, hp);
	colr_addr = (unsigned char *)&img->data[(int)(img->height * uv.v) * \
img->size_line + (int)(img->width * uv.u) * img->bpp / 8];
	texel = int_to_tcolr(get_intcolr_from_data(colr_addr, img->bpp / 8));
	return (texel);
}
