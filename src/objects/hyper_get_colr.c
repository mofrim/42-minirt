/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_get_colr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:39:50 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/22 14:45:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colr	hyper_get_scolr(t_hyper h, t_v3 hp);
t_colr	hyper_get_checker_colr(t_hyper h, t_v3 hp);

/* Ahh, we couuuld generalize this function for all shapes... but, no. */
t_colr	hyper_get_colr(t_scene scene, t_objlst hobj, t_v3 hit)
{
	t_hyper	h;
	t_colr	colr_at_hitpoint;
	t_hp	hp;

	h = *(t_hyper *)hobj.obj;
	hp.loc = hit;
	hp.cam2hp = v3_normalize(v3_minus_vec(scene.cam->pos, hit));
	hp.scolr = hyper_get_scolr(h, hp.loc);
	hp.spec = h.spec;
	hp.normal = hyper_get_normal(hp.loc, h);
	colr_at_hitpoint = calculate_lights(scene, hp);
	return (colr_at_hitpoint);
}

/* Get the surface color for the hyper. */
// TODO add texture support here.
t_colr	hyper_get_scolr(t_hyper h, t_v3 hp)
{
	if (h.checker)
		return (hyper_get_checker_colr(h, hp));
	return (h.colr);
}

// TODO comment
t_uv	hyper_get_uv(t_hyper h, t_v3 hp)
{
	t_uv	res;
	double	vmin;
	double	vmax;

	if (h.checker == 1)
		hp = v3_minus_vec(hp, h.center);
	if (h.checker == 2 || h.checker == 3)
		hp = v3_normalize(v3_minus_vec(hp, h.center));
	res.u = atan2(hp.z / h.ab, hp.x / h.ab) + M_PI;
	if (h.checker == 3)
		res.u = atan2(hp.y / h.ab, hp.x / h.ab) + M_PI;
	res.v = acosh(1 / h.ab * sqrt((hp.x * hp.x) + (hp.z * hp.z)));
	if (hp.y < 0)
		res.v = -res.v;
	res.u /= 2 * M_PI;
	vmin = asinh(v3_add_vec(h.center, v3_mult(h.axis, -h.h / 2)).y / h.c);
	vmax = asinh(v3_add_vec(h.center, v3_mult(h.axis, h.h / 2)).y / h.c);
	res.v = (res.v - vmin) / (vmax - vmin);
	res.u = fmod(res.u, 1.0);
	if (res.u < 0)
		res.u += 1.0;
	res.v = fmax(0.0, fmin(1.0, res.v));
	return (res);
}

/* Return checker pattern color. */
// in principle also generalizable
t_colr	hyper_get_checker_colr(t_hyper h, t_v3 hp)
{
	t_uv	uv;
	int		checker_u;
	int		checker_v;

	uv = hyper_get_uv(h, hp);
	checker_u = floor(h.checker_scale * uv.u);
	checker_v = floor(h.checker_scale * uv.v);
	if (((checker_u + checker_v) % 2) == 0)
		return (colr_get_darker(h.colr));
	return (colr_get_brightest(h.colr));
}
