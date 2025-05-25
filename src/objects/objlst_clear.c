/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objlst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:21:42 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 20:25:35 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* NOTE for now we do not use mlx_destroy_image here because this only works for
 * images that at least got displayed once. We don't do that i guess, bc we only
 * need the xpm reading routine from mlx and after that we work with the image
 * on our own. But i am not yet sure about that yet... */
static void	free_sphere(t_sphere *s)
{
	if (s->tex_file)
		free(s->tex_file);
	if (s->nmap_file)
		free(s->nmap_file);
	if (s->tex_img)
	{
		free(s->tex_img->image);
		free(s->tex_img);
	}
	if (s->nmap_img)
	{
		free(s->nmap_img->image);
		free(s->nmap_img);
	}
	free(s);
}

static void	free_hyper(t_hyper *h)
{
	if (h->tex_file)
		free(h->tex_file);
	if (h->tex_img)
	{
		free(h->tex_img->image);
		free(h->tex_img);
	}
	free(h);
}

void	objlst_clear(t_objlst *lst)
{
	t_objlst	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->type == SPHERE)
			free_sphere(lst->obj);
		else if (lst->type == HYPER)
			free_hyper(lst->obj);
		else
			free(lst->obj);
		free(lst);
		lst = tmp;
	}
}
