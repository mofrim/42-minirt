/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_get_scolr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:49:22 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/23 00:11:32 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colr	sphere_get_checker_colr(t_sphere s, t_v3 hp);
t_colr	sphere_get_tex_colr(t_sphere s, t_v3 hp);

/**
 * Get at hitpoint either from texture or obj_colr.
 *
 * Here all the u/v trafo is happening among other things.
 */
t_colr	sphere_get_scolr(t_sphere s, t_v3 hp)
{
	if (!s.tex_img && !s.checker)
		return (s.colr);
	if (s.checker)
		return (sphere_get_checker_colr(s, hp));
	return (sphere_get_tex_colr(s, hp));
}

/* Return the color from a texture. */
t_colr	sphere_get_tex_colr(t_sphere s, t_v3 hp)
{
	t_uv			uv;
	t_colr			texel;
	unsigned char	*colr_addr;
	t_img			*img;

	img = s.tex_img;
	uv = sphere_get_uv(s, hp);
	colr_addr = (unsigned char *)&img->data[(int)(img->height * uv.v) * \
img->size_line + (int)(img->width * uv.u) * img->bpp / 8];
	texel = int_to_tcolr(get_intcolr_from_data(colr_addr, img->bpp / 8));
	return (texel);
}

/* Return checker pattern color. */
t_colr	sphere_get_checker_colr(t_sphere s, t_v3 hp)
{
	t_uv	uv;
	int		checker_u;
	int		checker_v;

	uv = sphere_get_uv(s, hp);
	checker_u = floor(s.checker_scale * uv.u);
	checker_v = floor(s.checker_scale * uv.v / 2);
	if (((checker_u + checker_v) % 2) == 0)
		return (colr_get_darker(s.colr));
	return (colr_get_brightest(s.colr));
}
