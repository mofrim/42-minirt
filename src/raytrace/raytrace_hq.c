/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_hq.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:23:55 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 17:09:43 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	accumulate_colr(t_colr_int *acc, double x, double y, t_scene scene)
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

t_colr	supersample_pixel(int cx, int cy, t_scene scene)
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
			x_setoff = cx + scene.sample_step * (double)i / scene.samples_ppx;
			y_setoff = cy + scene.sample_step * (double)j / scene.samples_ppx;
			accumulate_colr(&acc, x_setoff, y_setoff, scene);
		}
	}
	i = (scene.samples_ppx + 1) * (scene.samples_ppx + 1);
	acc.r /= i;
	acc.g /= i;
	acc.b /= i;
	acc.i /= i;
	return ((t_colr){acc.r, acc.g, acc.b, acc.i});
}

void	raytrace_xpm_hq(t_mrt mrt)
{
	int		cx;
	int		cy;
	t_colr	pxcolr;

	cx = mrt.can_params.pixel_minx;
	while (cx < mrt.can_params.pixel_maxx)
	{
		cy = mrt.can_params.pixel_miny;
		while (cy < mrt.can_params.pixel_maxy)
		{
			pxcolr = supersample_pixel(cx, cy, *mrt.scene);
			put_pixel_xpm(mrt, cx, cy, pxcolr);
			cy++;
		}
		if (!(cx % 30))
			ft_printf(".");
		cx++;
	}
	ft_printf(" done.\n");
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.xc->img,
		mrt.can_params.sidebarx, 0);
}
