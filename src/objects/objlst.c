/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:53:28 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/10 12:57:42 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_objlst	*objlst_new(t_objtype type, void *obj)
{
	t_objlst	*new;

	new = malloc(sizeof(t_objlst));
	new->type = type;
	new->id = 0;
	new->next = NULL;
	if (type == SPHERE)
		new->obj = (t_sphere *)obj;
	if (type == PLANE)
		new->obj = (t_plane *)obj;
	if (type == CYLINDER)
		new->obj = (t_cylinder *)obj;
	if (type == LIGHT)
		new->obj = (t_light *)obj;
	if (type == CIRCLE)
		new->obj = (t_circle *)obj;
	if (type == TRIANGLE)
		new->obj = (t_triangle *)obj;
	if (type == HYPER)
		new->obj = (t_hyper *)obj;
	return (new);
}

t_objlst	*objlst_last(t_objlst *head)
{
	t_objlst	*cur;

	if (!head)
		return (NULL);
	cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

void	objlst_add_back(t_objlst **head, t_objlst *newend)
{
	t_objlst	*last;

	if (!newend)
		return ;
	if (!*head)
	{
		*head = newend;
		return ;
	}
	last = objlst_last(*head);
	last->next = newend;
	newend->id = last->id + 1;
}

/* NOTE for now we do not use mlx_destroy_image here because this only works for
 * images that at least got displayed once. We don't do that i guess, bc we only
 * need the xpm reading routine from mlx and after that we work with the image
 * on our own. But i am not yet sure about that yet... */
// FIXME if we really do not use mlx_destroy_image we do not need mrt as a param
// here, fucking fuck
static void	free_sphere(t_mrt mrt, t_sphere *s)
{
	(void)mrt;
	if (s->tex_file)
		free(s->tex_file);
	if (s->nmap_file)
		free(s->nmap_file);
	if (s->tex_img)
	{
		// mlx_destroy_image(mrt.mlx, s->tex_img);
		free(s->tex_img->image);
		free(s->tex_img);
	}
	if (s->nmap_img)
	{
		// mlx_destroy_image(mrt.mlx, s->nmap_img);
		free(s->nmap_img->image);
		free(s->nmap_img);
	}
	free(s);
}

void	objlst_clear(t_mrt mrt, t_objlst *lst)
{
	t_objlst	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->type != SPHERE)
			free(lst->obj);
		else
			free_sphere(mrt, lst->obj);
		free(lst);
		lst = tmp;
	}
}
