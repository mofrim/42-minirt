/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:33:27 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 18:15:35 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "xpm.h"

/**
 * Init xpm canvas and check endianess.
 *
 * Once again: 'big endian' = most significant bit goes first, 'little endian' =
 * least significant bit first. I.e. 0x11223344 -> 11223344 in big endian mem
 * vs. 44332211 in little endian mem.
 *
 * On different screens and machines we could have different pixel densities.
 * This is the significance of the 'bpp = bits per pixel' var. 'opp = octets per
 * pixel' is a convenience var easily indexing the in memory canvas array.
 */
t_xpm_canvas	*init_xpm_canvas(t_xvar *mlx, int width, int height)
{
	t_xpm_canvas	*xcanv;
	int				bpp;
	int				xl;
	int				endian;
	int				a;

	xcanv = malloc(sizeof(t_xpm_canvas));
	xcanv->mlx = mlx;
	xcanv->img = mlx_new_image(mlx, width, height);
	xcanv->data = (unsigned char *)mlx_get_data_addr(xcanv->img, &bpp, &xl,
			&endian);
	xcanv->bpp = bpp;
	xcanv->opp = bpp / 8;
	xcanv->xpm_line_len = xl;
	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		xcanv->endian = 1;
	else
		xcanv->endian = 0;
	return (xcanv);
}

/**
 * Put a pixel to the xpm in mem.
 *
 * Well... ptr is first set to the correct vertical line in our xpm array in
 * mem. in raytrace_xpm() we start at PIXEL_MINY with y coord. which is the min
 * possible y-value visible on the canvas. On our canvas this corresponds to the
 * line at the bottom. In mem, the xpm is saved in the computer graphics
 * coordinate where the origin is the upper left corner of the screen. So with y
 * == PIXEL_MINY we would end up at the last "row" of the xpm array. As the
 * xpm array is just a 1d-array in mem we need the `xpm_line_len` in bytes to
 * skip to the correct line.
 * Finally our t_colr is converted back to int which then is mapped to
 * mlx_get_color_value whose job it is to ensure the color is correctly
 * converted according to the bpp we need on the system we are compiling on.
 * Nowadays at least 24bit is standard everywhere.
 * Most finally and most hackily the mem is set to the correct value indexing
 * the 32bit int var as an unsigned char array ^^
 */
int	put_pixel_xpm(t_mrt mrt, int x, int y, t_colr colr)
{
	int				dec;
	int				color;
	unsigned char	*ptr;
	t_xpm_canvas	*xc;
	t_canvas_params	cp;

	xc = mrt.xc;
	cp = mrt.can_params;
	if (x > cp.pixel_maxx || y > cp.pixel_maxy)
		return (-1);
	ptr = &xc->data[(cp.pixel_maxy - y) * xc->xpm_line_len];
	color = mlx_get_color_value(xc->mlx, tcolr_to_int(colr));
	dec = xc->opp;
	while (dec--)
		*(ptr + (cp.pixel_maxx + x) * xc->opp + dec) = \
((unsigned char *)(&color))[dec];
	return (0);
}
