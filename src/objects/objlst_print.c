/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objlst_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:07:08 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/04 11:42:45 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_light(t_objlst obj)
{
	int		id;
	t_light	l;


	id = obj.id;
	l = *((t_light *)obj.obj);
	printf("  [%2d] light { pos=(%.4f,%.4f,%.4f), colr=(%d,%d,%d),"
			" intens=%.4f }\n",
		id, l.pos.x, l.pos.y, l.pos.z,
		l.colr.r, l.colr.g, l.colr.b, l.bright);
}

static void print_sphere(t_objlst obj)
{
	int			id;
	t_sphere	s;

	id = obj.id;
	s = *((t_sphere *)obj.obj);
	printf("  [%2d] sphere { center=(%.4f,%.4f,%.4f), r=%.4f, r**2=%.4f"
			" colr=[%d,%d,%d] }\n",
			id,
			s.center.x,
			s.center.y,
			s.center.z,
			s.r,
			s.r_squared,
			s.colr.r,
			s.colr.g,
			s.colr.b);
}

static void print_circle(t_objlst obj)
{
	int			id;
	t_circle	c;

	id = obj.id;
	c = *((t_circle *)obj.obj);
	printf("  [%2d] circle { center=(%.4f,%.4f,%.4f), normal=(%.4f,%.4f,%.4f) r=%.4f"
			" colr=[%d,%d,%d] }\n",
			id,
			c.center.x,
			c.center.y,
			c.center.z,
			c.normal.x,
			c.normal.y,
			c.normal.z,
			c.r,
			c.colr.r,
			c.colr.g,
			c.colr.b);
}

void	objlst_print(t_objlst *lst)
{
	while (lst)
	{
		if (lst->type == SPHERE)
			print_sphere(*lst);
		if (lst->type == LIGHT)
			print_light(*lst);
		if (lst->type == CIRCLE)
			print_circle(*lst);
		lst = lst->next;
	}
}
