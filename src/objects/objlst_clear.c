/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objlst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:21:42 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 20:36:40 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Free a sphere obj.
 *
 * We don't use mlx_destroy_image here, because this only works for images
 * created with mlx_new_image. This function uses X shared mem, which has to be
 * freed differently. We are only interested in storing the data somewhere. But
 * it would be an intersting point to investigate, if using shared mem has some
 * advantage..
 */
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

/* Free a hyper. */
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

/* Clear the objlst. */
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
