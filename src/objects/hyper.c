/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:41:08 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 23:12:29 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hyper_boloid_intersect(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
			t_hyper hyp);
double	hyper_caps_intersect(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
			t_hyper hyp);

/**
 * The top-level intersection func for the hyperbol.
 *
 * Combines the intersection with the main finite hyperbol and the caps and
 * returns the closer one.
 */
double	hyper_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_hyper *hyp)
{
	double	t;
	double	tcap;

	t = hyper_boloid_intersect(origin, ray_dir, rp, *hyp);
	tcap = hyper_caps_intersect(origin, ray_dir, rp, *hyp);
	if (tcap < t)
		return (tcap);
	return (t);
}

/**
 * Intersect the ray with the hyperbol's caps.
 *
 * We create the two caps as circle objs and then use our circle_intersect_ray
 * func to find a possible intersection. Smart, isn't it :)
 */
double	hyper_caps_intersect(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_hyper hyp)
{
	double		t1;
	double		t2;

	t1 = circle_intersect_ray(origin, ray_dir, rp, &hyp.cap1);
	t2 = circle_intersect_ray(origin, ray_dir, rp, &hyp.cap2);
	if (rp.tmin < t1 && t1 < rp.tmax && (t1 < t2 || \
!(rp.tmin < t2 && t2 < rp.tmax)))
		return (t1);
	if (rp.tmin <= t2 && t2 < rp.tmax)
		return (t2);
	else
		return (INF);
}
