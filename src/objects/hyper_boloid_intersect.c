/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_boloid_intersect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:00:44 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 09:55:39 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool		is_on_finite_hyper(t_v3 orig, t_v3 ray, t_hyper hyp,
					double res);
static t_v2		solve_intersec_equ(t_v3 origin, t_v3 ray_dir, t_hyper hyp);

/**
 * The intersection with the main hyperbol NOT the caps.
 *
 * Well the if statement seems a bit bloated... maybe there is a way to shorten
 * this. The tricky part here is not to get false intersection with the infinite
 * hyperboloid which then would clip or disturb the true intersection with the
 * finite hyperbol. The first check has to be so extensive bc it might happen
 * f.ex. that we find 2 solns x1, x2 where x2 < x1 and in the valid range but x1
 * is on the finite hyper and x2 is not!
 */
double	hyper_boloid_intersect(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_hyper hyp)
{
	t_v2	res;

	res = solve_intersec_equ(origin, ray_dir, hyp);
	if (res.x1 == -42 && res.x2 == -42)
		return (INF);
	if (rp.tmin < res.x1 && res.x1 < rp.tmax && \
is_on_finite_hyper(origin, ray_dir, hyp, res.x1) && \
(res.x1 < res.x2 || !(rp.tmin < res.x2 && res.x2 < rp.tmax) || \
(is_on_finite_hyper(origin, ray_dir, hyp, res.x1) && \
!is_on_finite_hyper(origin, ray_dir, hyp, res.x2))))
		return (res.x1);
	if (rp.tmin < res.x2 && res.x2 < rp.tmax && \
is_on_finite_hyper(origin, ray_dir, hyp, res.x2))
		return (res.x2);
	return (INF);
}

/* Check if hitpoint is on the finite hyperbol by projecting it on to the axis
 * of the hyperbol. */
bool	is_on_finite_hyper(t_v3 orig, t_v3 ray, t_hyper hyp, double res)
{
	t_v3	hit;

	hit = v3_add_vec(orig, v3_mult(ray, res));
	if (fabs(v3_dot(v3_minus_vec(hit, hyp.center), hyp.axis)) > hyp.hby2)
		return (false);
	return (true);
}

/**
 * The hyperboloid intersection equation.
 *
 * Substitute the ray `O + t * ray_dir` into the generalized hyperboloid formula
 * `(x - v)^T A (x - v)` where `x` is a point on the hyperboloid, `v` is the
 * axis and A is the hyper-matrix... and solve for `t`. The result is luckily
 * once again a quadratic formula.
 */
t_v2	solve_intersec_equ(t_v3 origin, t_v3 ray_dir, t_hyper hyp)
{
	t_v3	oc;
	double	p;
	double	q;
	double	disc;
	double	at;

	at = v3_dot(ray_dir, mtrx_prod_v3(hyp.hym, ray_dir));
	if (at == 0)
		return ((t_v2){-42, -42});
	oc = v3_minus_vec(origin, hyp.center);
	p = (v3_dot(ray_dir, mtrx_prod_v3(hyp.hym, oc)) \
+ v3_dot(oc, mtrx_prod_v3(hyp.hym, ray_dir))) / at;
	q = (v3_dot(oc, mtrx_prod_v3(hyp.hym, oc)) - 1) / at;
	disc = p * p / 4 - q;
	if (disc < 0)
		return ((t_v2){-42, -42});
	return ((t_v2){-p / 2 + sqrt(disc), -p / 2 - sqrt(disc)});
}
