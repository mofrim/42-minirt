/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_mtrx_colr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:50:10 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/02 11:42:26 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define	EPS 0.000000000001f

t_v3	get_normal_hyper(t_v3 hit, t_hyper hyp)
{
	t_v3	normal;
	t_v3	p;
	double	pn;

	p = v3_minus_vec(hit, hyp.center);
	pn = v3_norm(p);
	if (fabs(v3_dot(p, hyp.axis) - hyp.h/2) <= EPS && \
			sqrt(pn*pn - (hyp.h*hyp.h/4)) <= hyp.rcaps)
		return (hyp.axis);
	if (fabs(v3_dot(p, hyp.axis) + hyp.h / 2) <= EPS && \
			sqrt(pn*pn - (hyp.h*hyp.h/4)) <= hyp.rcaps)
		return (v3_mult(hyp.axis, -1));
	normal = v3_mult(mtrx_prod_vec(hyp.A, v3_minus_vec(hit, hyp.axis)), 2);
	return (v3_normalize(normal));
}

t_colr	hyper_get_colr(t_scene scene, t_objlst hobj, t_v3 hit)
{
	t_hyper	h;
	t_colr	colr_at_hitpoint;
	t_hp	hp;

	h = *(t_hyper *)hobj.obj;
	hp.scolr = h.colr;
	hp.loc = hit;
	hp.normal = get_normal_hyper(hp.loc, h);
	colr_at_hitpoint = calculate_lights(scene, hp);
	return (colr_at_hitpoint);
}

/* Adjusted get_rotmtrx func assuming that the default orientation of a
 * hyperboloid was along the y axis, i.e. (0,1,0) */
t_mtrx	get_rotmtrx_hyper(t_v3 axis, double ab, double c)
{
	t_v3	rot_axis;
	double	rot_angle;
	t_mtrx	id;
	t_mtrx	cross_matrix;
	t_mtrx	rot;

	rot_axis = v3_cross((t_v3){0, 0, 1}, axis);
	rot_angle = acos(v3_dot((t_v3){0, 0, 1}, axis));
	id = mtrx_new((t_v3){1, 0, 0}, (t_v3){0, 1, 0}, (t_v3){0, 0, 1});
	cross_matrix = mtrx_new((t_v3){0, rot_axis.z, -rot_axis.y},
			(t_v3){-rot_axis.z, 0, rot_axis.x},
			(t_v3){rot_axis.y, -rot_axis.x, 0});
	rot = mtrx_add_mtrx(mtrx_add_mtrx(id, mtrx_mult_scalar(cross_matrix, \
						sin(rot_angle))), \
				mtrx_mult_scalar(mtrx_prod_mtrx(cross_matrix, cross_matrix), \
					1 - cos(rot_angle)));
	return (mtrx_prod_mtrx(mtrx_prod_mtrx(rot,
				mtrx_new(
					(t_v3){1 / (ab * ab), 0, 0},
				(t_v3){0, 1 / (ab * ab), 0},
			(t_v3){0, 0, -1 / (c * c)})), mtrx_transpose(rot)));
}
