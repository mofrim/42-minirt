/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tex_nmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:04:09 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 20:29:03 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sphere_get_texnmap_imgs_from_file(t_mrt mrt, t_sphere *s)
{
	int	width;
	int	height;

	if (s->tex_file)
	{
		ft_printf("-> reading tex_file \n");
		s->tex_img = mlx_xpm_file_to_image(mrt.mlx,
				s->tex_file, &width, &height);
		if (!s->tex_img)
			printf("-> no valid tex image found! nevermind.\n");
	}
	if (s->nmap_file)
	{
		ft_printf("-> reading nmap_file \n");
		s->nmap_img = mlx_xpm_file_to_image(mrt.mlx,
				s->nmap_file, &width, &height);
		if (!s->nmap_img)
			printf("-> no valid nmap image found! nevermind.\n");
	}
}

/* Read a tex-file for the hyper. */
static void	hyper_get_tex_img_from_file(t_mrt mrt, t_hyper *h)
{
	int	width;
	int	height;

	if (h->tex_file)
	{
		ft_printf("-> reading tex_file \n");
		h->tex_img = mlx_xpm_file_to_image(mrt.mlx,
				h->tex_file, &width, &height);
		if (!h->tex_img)
			printf("-> no valid tex image found! nevermind.\n");
	}
}

/**
 * Read the nmap/texture files specified in scenefile.
 *
 * Implemeted so far only for sphere and hyper.
 */
void	read_tex_nmap(t_mrt mrt)
{
	t_objlst	*objs;

	objs = mrt.scene->objects;
	while (objs)
	{
		if (objs->type == SPHERE)
			sphere_get_texnmap_imgs_from_file(mrt, objs->obj);
		else if (objs->type == HYPER)
			hyper_get_tex_img_from_file(mrt, objs->obj);
		objs = objs->next;
	}
}
