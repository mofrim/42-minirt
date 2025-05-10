/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_get_scolr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:49:22 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/10 19:23:49 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Re-using this function from export_ppm :) :) :) */
int	get_intcolr_from_data(unsigned char *addr, int opp);

/**
 * Get at hitpoint either from texture or obj_colr.
 *
 * Here all the u/v trafo is happening among other.
 */
t_colr	get_scolr_sphere(t_sphere s, t_v3 hp)
{
	double			u;
	double			v;
	t_colr			texel;
	unsigned char	*colr_addr;
	t_img			*img;

	hp = v3_normalize(v3_minus_vec(hp, s.center));
	img = s.tex_img;
	if (!s.tex_img)
		return (s.colr);
	u = (atan2(hp.z, hp.x) + M_PI) / (2 * M_PI);
	v = acos(hp.y) / M_PI;
	colr_addr = (unsigned char *)&img->data[(int)(img->height * v) * \
img->size_line + (int)(img->width * u) * img->bpp / 8];
	texel = int_to_tcolr(get_intcolr_from_data(colr_addr, img->bpp / 8));
	return (texel);
}
