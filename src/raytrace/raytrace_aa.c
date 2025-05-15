/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_aa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:23:55 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/15 15:45:02 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	supersample_px(t_colr_int *acc, double x, double y, t_scene scene)
{
	t_v3	ray_dir;
	t_colr	px_colr;

	ray_dir = canvas2viewport(x, y, *scene.cam);
	px_colr = traceray(scene, ray_dir);
	acc->r += px_colr.r;
	acc->g += px_colr.g;
	acc->b += px_colr.b;
	acc->i += px_colr.i;
}

static t_colr	supersample_pixel(int cx, int cy, t_scene scene)
{
	int			i;
	int			j;
	t_colr_int	acc;
	double		x_setoff;
	double		y_setoff;

	acc = (t_colr_int){0, 0, 0, 1};
	i = -scene.samples_ppx_half - 1;
	while (++i <= scene.samples_ppx_half)
	{
		j = -scene.samples_ppx_half - 1;
		while (++j <= scene.samples_ppx_half)
		{
			x_setoff = cx + (double)i / scene.samples_ppx;
			y_setoff = cy + (double)j / scene.samples_ppx;
			supersample_px(&acc, x_setoff, y_setoff, scene);
		}
	}
	acc.r /= (scene.samples_ppx + 1) * (scene.samples_ppx + 1);
	acc.g /= (scene.samples_ppx + 1) * (scene.samples_ppx + 1);
	acc.b /= (scene.samples_ppx + 1) * (scene.samples_ppx + 1);
	acc.i /= (scene.samples_ppx + 1) * (scene.samples_ppx + 1);
	return ((t_colr){acc.r, acc.g, acc.b, acc.i});
}

void	raytrace_xpm_aa(t_mrt mrt)
{
	int		cx;
	int		cy;
	t_colr	pxcolr;

	cx = PIXEL_MINX;
	while (cx < PIXEL_MAXX)
	{
		cy = PIXEL_MINY;
		while (cy < PIXEL_MAXY)
		{
			pxcolr = supersample_pixel(cx, cy, *mrt.scene);
			put_pixel_xpm(mrt.xc, cx, cy, pxcolr);
			cy++;
		}
		if (!(cx % 100))
			ft_printf(".");
		cx++;
	}
	ft_printf(" done.\n");
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.xc->img, SIDEBAR_AREA_X, 0);
}
