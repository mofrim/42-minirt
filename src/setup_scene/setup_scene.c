/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:35:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/08 09:18:06 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_scene(t_scene *scene)
{
	if (scene->cam)
		setup_camera(scene->cam);
	if (!scene->objects)
		ft_printf("Warning: No objects in scene!\n");
}

void setup_camera(t_camera *cam)
{
	if (!cam)
		return ;
	cam->fov = cam->fov * M_PI / 180.0;
	cam->rot = get_rotmtrx(v3_get_norm(cam->orient));
	cam->view_width = 2 * tan(cam->fov / 2);
	cam->cvr = cam->view_width / CANVAS_WIDTH;
}
