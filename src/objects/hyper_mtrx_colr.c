/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_mtrx_colr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:50:10 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/15 10:31:19 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Get the normal for the hyperbolo
 *
 * At this point we now the hitpoint is a valid intersection either with the
 * caps or the main bolo. So in the first if statement we check wether the
 * projection of the hitpoint onto the bolo axis is at h/2 (within EPS
 * precission) if so, we want the normal of the top cap, so we return that. The
 * other case checks for -h/2 -> bottom cap.
 * The last case is a hit on the main bolo which leads to
 *
 * 		2 * A (hit - axis)
 *
 * being returned, which is the gradient at hitpoint of the bolo equation and in
 * this case the normal. As 2 is only a stretching factor, we omit it here. Also
 * the hit point has to be translated by the position of the center of the
 * hyper in order to get the correct normal for a hyper which is not centered at
 * (0,0,0).
 */
t_v3	get_normal_hyper(t_v3 hit, t_hyper hyp)
{
	t_v3	normal;
	t_v3	p;
	double	pn;

	p = v3_minus_vec(hit, hyp.center);
	pn = v3_norm(p);
	if (fabs(v3_dot(p, hyp.axis) - hyp.hby2) <= EPS && \
sqrt(pn * pn - (hyp.h * hyp.h / 4)) <= hyp.rcaps)
		return (hyp.axis);
	if (fabs(v3_dot(p, hyp.axis) + hyp.hby2) <= EPS && \
sqrt(pn * pn - (hyp.h * hyp.h / 4)) <= hyp.rcaps)
		return (v3_mult(hyp.axis, -1));
	normal = mtrx_prod_v3(hyp.hym,
			v3_minus_vec(v3_minus_vec(hit, hyp.center), hyp.axis));
	return (v3_normalize(normal));
}

/* Ahh, we couuuld generalize this function for all shapes... but, no. */
t_colr	hyper_get_colr(t_scene scene, t_objlst hobj, t_v3 hit)
{
	t_hyper	h;
	t_colr	colr_at_hitpoint;
	t_hp	hp;

	h = *(t_hyper *)hobj.obj;
	hp.loc = hit;
	hp.cam2hp = v3_normalize(v3_minus_vec(scene.cam->pos, hit));
	hp.scolr = h.colr;
	hp.spec = h.spec;
	hp.normal = get_normal_hyper(hp.loc, h);
	colr_at_hitpoint = calculate_lights(scene, hp);
	return (colr_at_hitpoint);
}

/* Adjusted get_rotmtrx func assuming that the default orientation of a
 * hyperboloid was along the z axis, i.e. (0,0,1). The final return value is 
 * 		R A R^t
 * where R is the rotation matrix to transform any v3 into a coordinate system
 * where the bolos axis is again aligned with the z-axis. So, what we end up
 * doing when we mtrx_prod with the returned matrix is: we transform the vector
 * into this special bolo-coord-system then we apply the bolo matrix and
 * afterwards we transform back the result. */
t_mtrx	hyper_get_rotmtrx(t_v3 axis, double ab, double c)
{
	t_v3	rot_axis;
	double	rot_angle;
	t_mtrx	id;
	t_mtrx	cross_matrix;
	t_mtrx	rot;

	rot_axis = v3_normalize(v3_cross((t_v3){0, 0, 1}, axis));
	rot_angle = acos(v3_dot((t_v3){0, 0, 1}, axis));
	id = mtrx_new((t_v3){1, 0, 0}, (t_v3){0, 1, 0}, (t_v3){0, 0, 1});
	cross_matrix = mtrx_new((t_v3){0, rot_axis.z, -rot_axis.y},
			(t_v3){-rot_axis.z, 0, rot_axis.x},
			(t_v3){rot_axis.y, -rot_axis.x, 0});
	rot = mtrx_add_mtrx(mtrx_add_mtrx(id, mtrx_mult_scalar(cross_matrix,
					sin(rot_angle))),
			mtrx_mult_scalar(mtrx_prod_mtrx(cross_matrix, cross_matrix),
				1 - cos(rot_angle)));
	return (mtrx_prod_mtrx(mtrx_prod_mtrx(rot,
				mtrx_new(
					(t_v3){1 / (ab * ab), 0, 0},
				(t_v3){0, 1 / (ab * ab), 0},
			(t_v3){0, 0, -1 / (c * c)})), mtrx_transpose(rot)));
}
