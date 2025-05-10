/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:34:50 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/10 19:27:51 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Keep for now. Nice to have some info on the imgs we parse. */
void	print_img_info(t_objlst *objs)
{
	t_sphere	*s;

	while (objs)
	{
		if (objs->type == SPHERE && (*(t_sphere *)objs->obj).tex_img)
		{
			s = (t_sphere *)objs->obj;
			printf("s->tex_img->height = %d\n", s->tex_img->height);
			printf("s->tex_img->width = %d\n", s->tex_img->width);
			printf("s->tex_img->size_line = %d\n", s->tex_img->size_line);
			printf("s->tex_img->bpp = %d\n", s->tex_img->bpp);
		}
		objs = objs->next;
	}
}

/**
 * Small but important: draw our minirt to the window!
 *
 * Aka `do_stuff`.
 */
void	launch_ui(t_mrt mrt)
{
	show_sidebar(mrt);
	print_scene(*mrt.scene);
	print_img_info(mrt.scene->objects);
	if (mrt.scene->alight && mrt.scene->cam)
	{
		printf("doing the trace!\n");
		raytrace_xpm(mrt);
	}
}
