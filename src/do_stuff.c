/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:29:11 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/09 13:28:18 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void draw_axis(t_mrt mrt)
{
	int i;
	t_colr	c = {42, 42, 42};

	i = -1;
	while (++i < CANVAS_WIDTH)
	{
		put_pixel_canvas_rt(mrt, (t_pxl){i, 0}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){-i, 0}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){0, i}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){0, -i}, c);
	}
}

// WARNING: the range for FOV is only (0, 180) meaning 0 and 180 not included!!!
// Explanation: 180deg would lead to a infinitely large vierwport width. 0 to 0.
// We need to check for that during map parsing!!!
void	init_cam(t_mrt mrt)
{
	t_camera	*cam;

	mrt.scene->cam = malloc(sizeof(t_camera));
	cam = mrt.scene->cam;
	cam->pos = v3_new(0, 5, 10);
	cam->look_at = v3_new(0, -1, 0);
	cam->fov = M_PI_4;
	cam->up = v3_new(0, 1, 0);
	cam->view_width = 2 * tan(cam->fov/2);
	cam->canvas_to_view_ratio = cam->view_width / CANVAS_WIDTH;
	printf("cam->viewport_width = %lf\n", cam->view_width);
}

void	init_objs(t_mrt mrt)
{
	t_objlst	**objs;

	objs = &mrt.scene->objects;
	t_sphere	*sphere1 = malloc(sizeof(t_sphere));
	*sphere1 = (t_sphere){v3_new(0, 0, 10), 2, 2 * 2, (t_colr){255, 0, 0}};
	t_sphere	*sphere2 = malloc(sizeof(t_sphere));
	*sphere2 = (t_sphere){v3_new(2, 0, 10), 2, 2 * 2, (t_colr){0, 255, 0}};
	t_sphere	*sphere3 = malloc(sizeof(t_sphere));
	*sphere3 = (t_sphere){v3_new(-2, 0, 9), 1.5, 1.5 * 1.5, (t_colr){0, 0, 142}};
	t_sphere	*sphere4 = malloc(sizeof(t_sphere));
	*sphere4 = (t_sphere){v3_new(-12, 0, 9), 1.5, 1.5 * 1.5, (t_colr){42, 42, 142}};
	t_sphere	*sphere5 = malloc(sizeof(t_sphere));
	*sphere5 = (t_sphere){v3_new(0, 12, 9), 1.5, 1.5 * 1.5, (t_colr){42, 42, 142}};
	t_sphere	*sphere6 = malloc(sizeof(t_sphere));
	*sphere6 = (t_sphere){v3_new(-6, 0, 9), 1.5, 1.5 * 1.5, (t_colr){42, 42, 142}};
	mrt.scene->objects = NULL;
	objlst_add_back(objs, objlst_new(SPHERE, sphere1));
	objlst_add_back(objs, objlst_new(SPHERE, sphere2));
	objlst_add_back(objs, objlst_new(SPHERE, sphere3));
	objlst_add_back(objs, objlst_new(SPHERE, sphere4));
	objlst_add_back(objs, objlst_new(SPHERE, sphere5));
	objlst_add_back(objs, objlst_new(SPHERE, sphere6));
}

void	init_lights(t_mrt mrt)
{
	mrt.scene->alight = malloc(sizeof(t_amb_light));
	mrt.scene->alight->ratio = 0.2;
	mrt.scene->alight->colr = (t_colr){42, 42, 42};
}

void	init_scene(t_mrt mrt)
{
	init_objs(mrt);
	init_cam(mrt);
	init_lights(mrt);
	mrt.scene->subsample = 1;
}

void	do_stuff(t_mrt mrt)
{
	init_scene(mrt);
	show_sidebar(mrt);
	print_scene(*mrt.scene);
	raytrace(mrt);
	draw_axis(mrt);
}

