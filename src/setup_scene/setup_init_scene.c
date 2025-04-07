/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_init_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:35:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/22 23:24:42 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_scene(t_scene *scene)
{
	if (scene->cam)
		setup_camera(scene->cam);
	if (!scene->alight)
	{
		scene->alight = malloc(sizeof(t_amb_light));
		if (scene->alight)
		{
			scene->alight->bright = 0.2;
			scene->alight->colr = (t_colr){255, 255, 255};
			ft_printf
			("Created def ambient light: bright=%f, color=(%d,%d,%d)\n",
					scene->alight->bright, scene->alight->colr.r,
					scene->alight->colr.g, scene->alight->colr.b);
		}
	}
	if (!scene->objects)
	{
		ft_printf("Warning: No objects in scene!\n");
	}
}

t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->objects = NULL;
	scene->alight = NULL;
	scene->cam = NULL;
	scene->subsample = 10;
	return (scene);
}
