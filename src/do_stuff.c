/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:29:11 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/22 22:17:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	init_cam(t_mrt mrt)
// {
// 	t_camera	*cam;

// 	mrt.scene->cam = malloc(sizeof(t_camera));
// 	cam = mrt.scene->cam;
// 	cam->pos = v3_new(0, 3, -3);
// 	cam->orient = v3_new(0, -1, 1.5);
// 	cam->fov = M_PI_4;
// 	cam->rot = get_rotmtrx(v3_get_norm(cam->orient));
// 	cam->view_width = 2 * tan(cam->fov/2);
// 	cam->cvr = cam->view_width / CANVAS_WIDTH;
// 	printf("cam->viewport_width = %lf\n", cam->view_width);
// }

// void setup_camera(t_camera *cam)
// {
// 	if (!cam)
// 		return ;
// 	// set up the rotation matrix
// 	cam->rot = get_rotmtrx(v3_get_norm(cam->orient));

// 	// Calculate view based on fov
// 	cam->view_width = 2 * tan(cam->fov / 2);

// 	//calculate canvas to viewport ratio
// 	cam->cvr = cam->view_width / CANVAS_WIDTH;

// 	ft_printf("cam->viewport_width = %lf\n", cam->view_width);
// }


void setup_camera(t_camera *cam)
{
	if (!cam)
		return;

	// Convert FOV from degrees to radians if needed
	if (cam->fov > M_PI)  // If FOV is likely in degrees
		cam->fov = cam->fov * M_PI / 180.0;

	// Set up the rotation matrix
	cam->rot = get_rotmtrx(v3_get_norm(cam->orient));

	// Calculate view based on fov
	cam->view_width = 2 * tan(cam->fov / 2);

	// Calculate canvas to viewport ratio
	cam->cvr = cam->view_width / CANVAS_WIDTH;

	printf("Camera setup: pos=(%f,%f,%f), orient=(%f,%f,%f), fov=%f rad, width=%f\n",
		   cam->pos.x, cam->pos.y, cam->pos.z,
		   cam->orient.x, cam->orient.y, cam->orient.z,
		   cam->fov, cam->view_width);
}




// void	init_objs(t_mrt mrt)
// {
// 	t_objlst	**objs;

// 	mrt.scene->objects = NULL;
// 	objs = &mrt.scene->objects;
// 	t_sphere	*sphere1 = malloc(sizeof(t_sphere));
// 	*sphere1 = (t_sphere){v3_new(0, 0, 10), 2, 2 * 2, (t_colr){255, 0, 0}};
// 	t_sphere	*sphere2 = malloc(sizeof(t_sphere));
// 	*sphere2 = (t_sphere){v3_new(4, 0, 14), 2, 2 * 2, (t_colr){0, 255, 0}};
// 	t_sphere	*sphere3 = malloc(sizeof(t_sphere));
// 	*sphere3 = (t_sphere){v3_new(-4, 0, 14), 1.5, 1.5 * 1.5, (t_colr){0, 0, 142}};
// 	t_sphere	*sphere4 = malloc(sizeof(t_sphere));
// 	*sphere4 = (t_sphere){v3_new(-2, -1, 8), 1.5, 1.5 * 1.5, (t_colr){0, 99, 142}};
// 	t_sphere	*sphere5 = malloc(sizeof(t_sphere));
// 	*sphere5 = (t_sphere){v3_new(2, -1, 8), 1, 1 * 1, (t_colr){123, 99, 142}};
// 	objlst_add_back(objs, objlst_new(SPHERE, sphere1));
// 	objlst_add_back(objs, objlst_new(SPHERE, sphere2));
// 	objlst_add_back(objs, objlst_new(SPHERE, sphere3));
// 	objlst_add_back(objs, objlst_new(SPHERE, sphere4));
// 	objlst_add_back(objs, objlst_new(SPHERE, sphere5));
// }

// void	init_lights(t_mrt mrt)
// {
// 	t_objlst	**objs;

// 	mrt.scene->alight = malloc(sizeof(t_amb_light));
// 	mrt.scene->alight->bright = 0.3;
// 	mrt.scene->alight->colr = (t_colr){255, 255, 255};

// 	objs = &mrt.scene->objects;

// 	t_light	*light1 = malloc(sizeof(t_light));
// 	light1->bright = 0.5;
// 	// light1->colr = (t_colr){255, 0, 0};
// 	light1->colr = (t_colr){255, 255, 255};
// 	light1->pos = (t_v3){0, 2.9, 10};
// 	objlst_add_back(objs, objlst_new(LIGHT, light1));

// 	t_light	*light2 = malloc(sizeof(t_light));
// 	light2->bright = 0.9;
// 	light2->colr = (t_colr){0, 0, 255};
// 	light2->pos = (t_v3){0, -2.1, 8};
// 	objlst_add_back(objs, objlst_new(LIGHT, light2));

// 	t_light	*light3 = malloc(sizeof(t_light));
// 	light3->bright = 0.9;
// 	light3->colr = (t_colr){200, 12, 23};
// 	light3->pos = (t_v3){0, 0, 7};
// 	objlst_add_back(objs, objlst_new(LIGHT, light3));

// 	t_light	*light4 = malloc(sizeof(t_light));
// 	light4->bright = 0.6;
// 	light4->colr = (t_colr){123, 231, 76};
// 	light4->pos = (t_v3){0, 5, 7};
// 	objlst_add_back(objs, objlst_new(LIGHT, light4));
// }

// void	init_scene(t_mrt mrt)
// {
// 	init_objs(mrt);
// 	init_cam(mrt);
// 	init_lights(mrt);
// 	mrt.scene->subsample = 1;
// }

void	do_stuff(t_mrt mrt)
{

	// init_scene(mrt);
	show_sidebar(mrt);
	print_scene(*mrt.scene);
	raytrace_xpm(mrt);
}

