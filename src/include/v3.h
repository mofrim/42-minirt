/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:49:45 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 22:52:39 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3_H
# define V3_H

/* A lighter 3d-vector struct. */
typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
}	t_v3;

/* Ops. */
t_v3	v3_add_scalar(t_v3 v, double d);
t_v3	v3_add_v3(t_v3 v, t_v3 w);
t_v3	v3_minus_v3(t_v3 v, t_v3 w);
t_v3	v3_mult(t_v3 v, double d);
double	v3_dot(t_v3 v, t_v3 w);
t_v3	v3_cross(t_v3 v, t_v3 w);
double	v3_norm(t_v3 v);
t_v3	v3_normalize(t_v3 v);
void	v3_print(t_v3 v, char *name);

#endif
