/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:23:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/02 08:44:13 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	canvas2viewport(int cx, int cy, t_camera cam);
t_colr	traceray(t_scene scene, t_v3 ray_dir);

/**
 * The main raytracing routine.
 *
 * So far this is complete. Any further development should be happening in the
 * subroutines.
 */
void	raytrace(t_mrt mrt)
{
	int		cx;
	int		cy;
	t_v3	ray_dir;
	t_colr	px_colr;

	cx = PIXEL_MINX;
	px_colr = mrt.scene->alight->colr;
	while (cx < PIXEL_MAXX)
	{
		cy = PIXEL_MINY;
		while (cy < PIXEL_MAXY)
		{
			ray_dir = canvas2viewport(cx, cy, *mrt.scene->cam);
			if (!(cy % mrt.scene->subsample))
				px_colr = traceray(*mrt.scene, ray_dir);
			put_pixel_canvas_rt(mrt, (t_pxl){cx, cy}, px_colr);
			cy++;
		}
		cx++;
	}
}

/**
 * Converts canvas coords to viewport coords.
 *
 * The Screen coordinates (params cx and cy) are given in our raytracing-canvas
 * coordinates where the middle of the canvas is the origin. The 2nd param is
 * the canvas2viewport_ratio.
 * We always want our viewport to be at a 1 unit distance from our camera ->
 * z = 1.
 *
 * Explanation vor the calculation:
 *
 * 	The book says V_x = C_x * V_w/C_w and V_y = C_y * V_h / C_h, where V_x, V_y
 * 	are the corresponding viewport coords to the Canvas-coords C_x, C_y. V_w,
 * 	V_h and C_w,C_h are the viewport / Canvas width / height. In our case the
 * 	viewport height V_h = V_w * WINY / CANVAS_WIDTH = V_w * C_h / C_w
 * 	=> V_h/C_h  = V_w / C_w. So the same canvas_to_view_ratio =: cvr hast to be
 * 	applied to both coords.
 */
t_v3	canvas2viewport(int cx, int cy, t_camera cam)
{
	t_v3	viewport_vec;

	viewport_vec.x = (double)cx * cam.cvr;
	viewport_vec.y = (double)cy * cam.cvr;
	viewport_vec.z = VIEWZ;
	return (mtrx_prod_vec(cam.rot, viewport_vec));
}

t_colr	traceray(t_scene scene, t_v3 ray_dir)
{
	t_intersec	intersec;
	t_v3		hitpoint;
	t_colr		colr_at_hitpoint;

	intersec = intersect_ray_objs(scene.cam->pos, ray_dir, \
			(t_ray_minmax){VIEWZ, INF}, scene.objects);
	hitpoint = v3_add_vec(scene.cam->pos, v3_mult(ray_dir, intersec.t));
	colr_at_hitpoint = get_object_colr(scene, intersec.obj, hitpoint);
	return (colr_at_hitpoint);
}
