/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:41:08 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/02 10:44:09 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hyper_boloid_intersect(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_hyper hyp);
double	hyper_caps_intersect(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_hyper hyp);

/**
 * The hyperboloid intersection equation.
 *
 * Substitute the ray `O + t * ray_dir` into the generalized hyperboloid formula
 * `(x - v)^T A (x - v)` where `x` is a point on the hyperboloid, `v` is the
 * axis and A is the hyper-matrix... and solve for `t`.
 */
double	hyper_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_hyper hyp)
{
	double	t;
	double	tcap;

	t = hyper_boloid_intersect(origin, ray_dir, rp, hyp);
	tcap = hyper_caps_intersect(origin, ray_dir, rp, hyp);
	if (tcap < t)
		return (tcap);
	return (t);
}

double	hyper_boloid_intersect(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_hyper hyp)
{
	t_v3	ov;
	double	p;
	double	q;
	double	disc;
	t_v2	res;

	ov = v3_minus_vec(origin, hyp.center);
	p = (v3_dot(ray_dir, mtrx_prod_vec(hyp.A, ov)) \
			+ v3_dot(ov, mtrx_prod_vec(hyp.A, ray_dir))) / \
			v3_dot(ray_dir, mtrx_prod_vec(hyp.A, ray_dir));
	q = (v3_dot(ov, mtrx_prod_vec(hyp.A, ov)) - 1) / \
		v3_dot(ray_dir, mtrx_prod_vec(hyp.A, ray_dir));
	disc = p * p / 4 - q;
	if (disc < 0)
		return (INF);
	res.x1 = - p / 2 + sqrt(disc);
	res.x2 = - p / 2 - sqrt(disc);
	if (rp.tmin < res.x1 && res.x1 < rp.tmax && (res.x1 < res.x2 || \
			!(rp.tmin < res.x2 && res.x2 < rp.tmax)))
	{
		t_v3 hit = v3_add_vec(origin, v3_mult(ray_dir, res.x1));
		if (fabs(v3_dot(v3_minus_vec(hit, hyp.center), hyp.axis)) > hyp.hby2)
			return (INF);
		return (res.x1);
	}
	if (rp.tmin < res.x2 && res.x2 < rp.tmax)
	{
		t_v3 hit = v3_add_vec(origin, v3_mult(ray_dir, res.x2));
		if (fabs(v3_dot(v3_minus_vec(hit, hyp.center), hyp.axis)) > hyp.hby2)
			return (INF);
		return (res.x2);
	}
	return (INF);
}

double	hyper_caps_intersect(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_hyper hyp)
{
	t_circle	c1;
	t_circle	c2;
	double		t;

	c1.center = v3_add_vec(hyp.center, v3_mult(hyp.axis, hyp.h / 2));
	c1.r = hyp.rcaps;
	c1.r2 = c1.r * c1.r;
	c1.normal = hyp.axis;
	c2.center = v3_minus_vec(hyp.center, v3_mult(hyp.axis, hyp.h / 2));
	c2.r = c1.r;
	c2.r2 = c1.r2;
	c2.normal = v3_mult(hyp.axis, -1);
	t = circle_intersect_ray(origin, ray_dir, rp, c1);
	if (t != INF)
		return (t);
	t = circle_intersect_ray(origin, ray_dir, rp, c2);
	if (t != INF)
		return (t);
	return (INF);
}
