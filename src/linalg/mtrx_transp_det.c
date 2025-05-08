/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx_transp_det.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:56:06 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 09:56:43 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Transpose a 3x3 mtrx. */
t_mtrx	mtrx_transpose(t_mtrx a)
{
	t_mtrx	r;

	r.m[0][0] = a.m[0][0];
	r.m[0][1] = a.m[1][0];
	r.m[0][2] = a.m[2][0];
	r.m[1][0] = a.m[0][1];
	r.m[1][1] = a.m[1][1];
	r.m[1][2] = a.m[2][1];
	r.m[2][0] = a.m[0][2];
	r.m[2][1] = a.m[1][2];
	r.m[2][2] = a.m[2][2];
	return (r);
}

/* Calculate the determinant of a 3x3 mtrxt. */
double	mtrx_det(t_mtrx a)
{
	double	d1;
	double	d2;
	double	d3;

	d1 = a.m[0][0] * (a.m[1][1] * a.m[2][2] - a.m[2][1] * a.m[1][2]);
	d2 = a.m[1][0] * (a.m[0][1] * a.m[2][2] - a.m[2][1] * a.m[0][2]);
	d3 = a.m[2][0] * (a.m[0][1] * a.m[1][2] - a.m[1][1] * a.m[0][2]);
	return (d1 - d2 + d3);
}
