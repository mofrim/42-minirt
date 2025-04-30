/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:35:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/30 16:58:28 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_cam_inside_obj(t_camera cam, t_scene scene);

/**
 * This is the post parsing setup function.
 *
 * .
 * TODO:
 * - do the ambient light calculation for every object in here.
 */
void	setup_scene(t_scene *scene)
{
	if (scene->cam)
		setup_camera(scene->cam, *scene);
	if (!scene->objects)
		ft_printf("Warning: No objects in scene!\n");
	scene->subsample = 10;
}

void setup_camera(t_camera *cam, t_scene scene)
{
	if (!cam)
		return ;
	cam->fov = cam->fov * M_PI / 180.0;
	cam->rot = get_rotmtrx(v3_normalize(cam->orient));
	cam->view_width = 2 * tan(cam->fov / 2);
	cam->cvr = cam->view_width / CANVAS_WIDTH;
	cam->is_inside_obj = is_cam_inside_obj(*cam, scene);
	cam->orient = v3_normalize(cam->orient);
}

static bool	is_inside_sphere(t_v3 pos, t_sphere sp)
{
	if (v3_norm(v3_minus_vec(pos, sp.center)) < sp.r)
		return (true);
	return (false);
}

bool	is_cam_inside_obj(t_camera cam, t_scene scene)
{
	t_objlst	*objs;

	objs = scene.objects;
	while (objs)
	{
		if (objs->type == SPHERE && is_inside_sphere(cam.pos, *(t_sphere *)objs->obj))
			return (true);
		objs = objs->next;
	}
	return (false);
}
