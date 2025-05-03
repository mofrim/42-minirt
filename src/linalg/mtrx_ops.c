/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:41:34 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/02 20:02:42 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Matrix * t_v3. Returns result */
t_v3	mtrx_prod_vec(t_mtrx a, t_v3 v)
{
	t_v3	res;

	res.x = v.x * a.m[0][0] + v.y * a.m[0][1] + v.z * a.m[0][2];
	res.y = v.x * a.m[1][0] + v.y * a.m[1][1] + v.z * a.m[1][2];
	res.z = v.x * a.m[2][0] + v.y * a.m[2][1] + v.z * a.m[2][2];
	return (res);
}

/* Add 2 3x3 matrices. */
t_mtrx	mtrx_add_mtrx(t_mtrx a, t_mtrx b)
{
	t_mtrx	c;
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			c.m[i][j] = a.m[i][j] + b.m[i][j];
	}
	return (c);
}

/* Add 2 3x3 matrices. */
t_mtrx	mtrx_mult_scalar(t_mtrx a, double c)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			a.m[i][j] = c * a.m[i][j];
	}
	return (a);
}

/* Matrix product of 2 matrices. */
t_mtrx	mtrx_prod_mtrx(t_mtrx a, t_mtrx b)
{
	t_mtrx	c;
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			c.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + \
				a.m[i][2] * b.m[2][j];
	}
	return (c);
}

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
