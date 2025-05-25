/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:35:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/05/25 18:59:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_cam_inside_obj(t_camera cam, t_scene scene);

/**
 * This is the post parsing setup function.
 *
 * The most important part in here is checking if the cam is inside some
 * object. This implies there won't be alight added to the colors. We can only
 * do it here because we need the whole scene to be parsed with all its objects
 * for being able to check the insideness of the cam. But maybe we will decide
 * to add other things or even all secondary calculations after parsing to this
 * functions.
 */
void	setup_scene(t_mrt mrt)
{
	t_scene	*scene;

	scene = mrt.scene;
	if (scene->cam)
		scene->cam->is_inside_obj = is_cam_inside_obj(*scene->cam, *scene);
	if (!scene->objects)
		ft_printf("Warning: No objects in scene!\n");
	if (!scene->alight)
	{
		scene->alight = malloc(sizeof(t_colr));
		*scene->alight = (t_colr){255, 255, 255, 0};
	}
	if (!scene->cam)
		put_string_canvas(mrt, (t_pxl){0, 0}, GREEN,
			"No cam specified... so there is nothing to be seen ;)");
	else
		put_string_canvas(mrt, (t_pxl){0, 0}, GREEN,
			"Loading Jose's & Mofrim's miniRT...");
	read_tex_nmap(mrt);
}

/* Is the cam inside of a sphere? */
static bool	is_inside_sphere(t_v3 pos, t_sphere sp)
{
	if (v3_norm(v3_minus_v3(pos, sp.center)) <= sp.r)
		return (true);
	return (false);
}

/* Loop over objlst and check for each object if the cam is inside of it. */
bool	is_cam_inside_obj(t_camera cam, t_scene scene)
{
	t_objlst	*objs;

	objs = scene.objects;
	while (objs)
	{
		if (objs->type == SPHERE && \
is_inside_sphere(cam.pos, *(t_sphere *)objs->obj))
			return (true);
		objs = objs->next;
	}
	return (false);
}
