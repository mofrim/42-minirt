/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtrx_new_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:41:34 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/10 09:13:52 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Returns a new t_mtrx with colum vectors c1,c2,c3. */
t_mtrx	mtrx_new(t_v3 c1, t_v3 c2, t_v3 c3)
{
	t_mtrx	a;

	a.m[0][0] = c1.x;
	a.m[1][0] = c1.y;
	a.m[2][0] = c1.z;
	a.m[0][1] = c2.x;
	a.m[1][1] = c2.y;
	a.m[2][1] = c2.z;
	a.m[0][2] = c3.x;
	a.m[1][2] = c3.y;
	a.m[2][2] = c3.z;
	return (a);
}

/* Print a mtrx to console. */
void	mtrx_print(t_mtrx a)
{
	int		i;
	int		j;

	i = -1;
	printf("[");
	while (++i < 3)
	{
		if (i != 0)
			printf(" ");
		j = -1;
		while (++j < 3)
			printf("%6.2lf ", a.m[i][j]);
		if (i != 2)
			printf("\n");
	}
	printf("]\n");
}
