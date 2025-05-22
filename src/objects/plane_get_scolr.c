/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_get_scolr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:29:07 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/22 12:09:20 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colr	plane_get_checker_colr(t_plane s, t_v3 hp);

/* Get surface colr of the plane. */
t_colr	plane_get_scolr(t_plane p, t_v3 hp)
{
	if (p.checker)
		return (plane_get_checker_colr(p, hp));
	return (p.colr);
}

/* Return the checker pattern colr for the plane. */
t_colr	plane_get_checker_colr(t_plane p, t_v3 hp)
{
	int	x;
	int	y;
	int	z;

	x = floor(hp.x * p.checker_scale);
	y = floor(hp.y * p.checker_scale);
	z = floor(hp.z * p.checker_scale);
	if (((x + y + z) % 2) == 0)
		return (colr_get_darker(p.colr));
	return (colr_get_brightest(p.colr));
}
