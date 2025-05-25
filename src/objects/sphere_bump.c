/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:34:40 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 18:59:08 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Helper func to avoid overflow in image-array indexing. */
static int	check_minmax(int val, int min, int max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}

/* u and v will always be in [0,1] because of their normalization by pi and 2pi
 * so there is no need to check this. */
t_colr	get_colr_uv(double u, double v, t_img *img)
{
	t_colr			c;
	unsigned char	*colr_addr;
	int				x;
	int				y;
	int				opp;

	opp = img->bpp / 8;
	x = (int)(u * img->width);
	y = (int)(v * img->height);
	x = check_minmax(x, 0, img->width - 1);
	y = check_minmax(y, 0, img->height - 1);
	colr_addr = (unsigned char *)&img->data[y * img->size_line + x * opp];
	c = int_to_tcolr(get_intcolr_from_data(colr_addr, opp));
	return (c);
}

/* Our height function atm Different stuff is thinkable here. This just adds up
 * all RGB values and normalizes the result to [0,1]. */
double	get_height(double u, double v, t_sphere s)
{
	t_colr	c;

	c = get_colr_uv(u, v, s.tex_img);
	return ((c.r + c.g + c.b) / (3 * 255.0f));
}

/* Get the pertubated normal */
static t_v3	get_bumped_normal(t_v3 n, double dhdu, double dhdv)
{
	t_v3	tangent;
	t_v3	bitangent;
	t_v3	bump_normal;

	tangent = sphere_get_tangent(n);
	bitangent = v3_normalize(v3_cross(n, tangent));
	bump_normal.x = n.x - dhdu * tangent.x - dhdv * bitangent.x;
	bump_normal.y = n.y - dhdu * tangent.y - dhdv * bitangent.y;
	bump_normal.z = n.z - dhdu * tangent.z - dhdv * bitangent.z;
	return (v3_normalize(bump_normal));
}

/* The main bump mapping function using the surface normal pertubation through
 * simple substraction of scaled tangent and bitangent. The scale factor is the
 * "derivative" of the height function in u and v dir. */
t_v3	sphere_bump(t_v3 n, t_sphere s)
{
	double	dhdu;
	double	dhdv;
	double	u;
	double	v;

	n = v3_normalize(v3_minus_v3(n, s.center));
	u = (atan2(n.z, n.x) + M_PI) / (2 * M_PI);
	v = acos(n.y) / M_PI;
	dhdu = s.bumpiness * s.tex_img->width * \
(get_height(u + 1.0 / s.tex_img->width, v, s) - get_height(u, v, s));
	dhdv = s.bumpiness * s.tex_img->height * \
(get_height(u, v + 1.0 / s.tex_img->height, s) - get_height(u, v, s));
	return (get_bumped_normal(n, dhdu, dhdv));
}

/* The cross-product pertubation approach... keep around until definitely
 * obsolete. */
// t_v3	sphere_bump_cross(t_v3 hp, t_sphere s)
// {
// 	double	u;
// 	double	v;
// 	double	dhdu;
// 	double	dhdv;
//
// 	hp = v3_normalize(v3_minus_vec(hp, s.center));
// 	u = (atan2(hp.z, hp.x) + M_PI) / (2 * M_PI);
// 	v = acos(hp.y) / M_PI;
// 	dhdu = s.bumpiness * s.tex_img->width *
// 	h(u + 1.0 / s.tex_img->width, v, s) - h(u, v, s);
// 	dhdv = s.bumpiness * s.tex_img->height *
// 	h(u, v + 1.0 / s.tex_img->height, s) - h(u, v, s);
// 	t_v3 tangent = get_tangent(hp);
// 	t_v3 bitangent = v3_normalize(v3_cross(hp, tangent));
// 	t_v3 dqdu = v3_add_vec(tangent, v3_mult(hp, dhdu));
// 	t_v3 dqdv = v3_add_vec(bitangent, v3_mult(hp, dhdv));
// 	return (v3_normalize(v3_cross(dqdv, dqdu)));
// }
