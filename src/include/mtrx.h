/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:20:13 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 09:55:39 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MTRX_H
# define MTRX_H

# include "v3.h"

typedef struct s_mtrx
{
	double	m[3][3];
}	t_mtrx;

t_v3	mtrx_prod_v3(t_mtrx a, t_v3 v);
t_mtrx	mtrx_add_mtrx(t_mtrx a, t_mtrx b);
t_mtrx	mtrx_mult_scalar(t_mtrx a, double c);
t_mtrx	mtrx_prod_mtrx(t_mtrx a, t_mtrx b);
t_mtrx	mtrx_new(t_v3 c1, t_v3 c2, t_v3 c3);
t_mtrx	mtrx_transpose(t_mtrx a);
double	mtrx_det(t_mtrx a);
void	mtrx_print(t_mtrx a);

#endif
