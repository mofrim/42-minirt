/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:23:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/11 10:59:57 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	canvas2viewport(int cx, int cy, t_camera cam);
t_colr	traceray(t_mrt mrt, t_v3 ray_dir);

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
				px_colr = traceray(mrt, ray_dir);
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

/**
 * The main action of tracing the rays intersection.
 *
 * Checks for the closest intersection with any obj from the objlst. Returns the
 * color the pixel to be printed.
 */
t_colr	traceray(t_mrt mrt , t_v3 ray_dir)
{
	double		closest_t;
	t_objlst	*closest_obj;
	t_objlst	*objs;
	double		t;

	objs = mrt.scene->objects;
	closest_t = INF;
	closest_obj = NULL;
	while (objs)
	{
		if (objs->type != LIGHT )
		{
			t = intersect_ray_obj(mrt.scene->cam->pos, ray_dir, objs);
			if (VIEWZ < t && t < INF && t < closest_t)
			{
				closest_t = t;
				closest_obj = objs;
			}
		}
		objs = objs->next;
	}
	if (closest_t != INF )
	{
		printf("hitpoint:\n");
		v3_print(v3_add_vec(mrt.scene->cam->pos, v3_mult(ray_dir, closest_t)));
		printf("\n");
	}
	return (get_object_colr(*mrt.scene, closest_obj,
				v3_add_vec(mrt.scene->cam->pos, v3_mult(ray_dir, closest_t))));
}
