/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:29:11 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/03 10:51:14 by fmaurer          ###   ########.fr       */
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

void	add_circle(t_mrt mrt)
{
	t_circle	*c = malloc(sizeof(t_circle));
	c->center = (t_v3){0, 0, 0};
	c->r = 10;
	c->r2 = c->r * c->r;
	c->normal = v3_get_norm((t_v3){0, 1, 0});
	c->colr = rgb_to_tcolr(DARK_SLATE_BLUE);
	objlst_add_back(&mrt.scene->objects, objlst_new(CIRCLE, c));

	t_circle	*c2 = malloc(sizeof(t_circle));
	c2->center = (t_v3){0, 0.01, 0};
	c2->r = 9;
	c2->r2 = c2->r * c2->r;
	c2->normal = v3_get_norm((t_v3){0, 1, 0});
	c2->colr = rgb_to_tcolr(MEDIUM_BLUE);
	objlst_add_back(&mrt.scene->objects, objlst_new(CIRCLE, c2));

	t_circle	*c3 = malloc(sizeof(t_circle));
	c3->center = (t_v3){0, 0.02, 0};
	c3->r = 8;
	c3->r2 = c3->r * c3->r;
	c3->normal = v3_get_norm((t_v3){0, 1, 0});
	c3->colr = rgb_to_tcolr(DODGER_BLUE);
	objlst_add_back(&mrt.scene->objects, objlst_new(CIRCLE, c3));

	t_circle	*c4 = malloc(sizeof(t_circle));
	c4->center = (t_v3){0, 0.03, 0};
	c4->r = 7;
	c4->r2 = c4->r * c4->r;
	c4->normal = v3_get_norm((t_v3){0, 1, 0});
	c4->colr = rgb_to_tcolr(DARK_SEA_GREEN);
	objlst_add_back(&mrt.scene->objects, objlst_new(CIRCLE, c4));

	t_circle	*c5 = malloc(sizeof(t_circle));
	c5->center = (t_v3){0, 0.04, 0};
	c5->r = 6;
	c5->r2 = c5->r * c5->r;
	c5->normal = v3_get_norm((t_v3){0, 1, 0});
	c5->colr = rgb_to_tcolr(GOLDENROD);
	objlst_add_back(&mrt.scene->objects, objlst_new(CIRCLE, c5));
}

void	do_stuff(t_mrt mrt)
{

	// init_scene(mrt);
	show_sidebar(mrt);
	add_circle(mrt);
	print_scene(*mrt.scene);
	raytrace_xpm(mrt);
}

