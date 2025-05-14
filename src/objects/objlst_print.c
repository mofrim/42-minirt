/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objlst_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:07:08 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/13 22:28:10 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Prototypes of all the subroutines only needed in here. */
void	print_hyper(t_objlst obj);
void	print_light(t_objlst obj);
void	print_sphere(t_objlst obj);
void	print_circle(t_objlst obj);
void	print_triangle(t_objlst obj);

/* Print the whole objlst. */
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
		if (lst->type == TRIANGLE)
			print_triangle(*lst);
		if (lst->type == HYPER)
			print_hyper(*lst);
		lst = lst->next;
	}
}

void	print_light(t_objlst obj)
{
	int		id;
	t_light	l;

	id = obj.id;
	l = *((t_light *)obj.obj);
	printf("  [%2d] light { pos=(%.4f,%.4f,%.4f), colr=(%d,%d,%d),"
		" intens=%.4f }\n",
		id, l.pos.x, l.pos.y, l.pos.z,
		l.colr.r, l.colr.g, l.colr.b, l.colr.i);
}

void	print_sphere(t_objlst obj)
{
	int			id;
	t_sphere	s;

	id = obj.id;
	s = *((t_sphere *)obj.obj);
	printf("  [%2d] sphere { center=(%.4f,%.4f,%.4f), r=%.4f, r**2=%.4f"
		" colr=[%d,%d,%d], tex='%s', nmap='%s', bump='%d' }\n",
		id,
		s.center.x,
		s.center.y,
		s.center.z,
		s.r,
		s.r_squared,
		s.colr.r,
		s.colr.g,
		s.colr.b,
		s.tex_file,
		s.nmap_file,
		s.bump);
}

void	print_circle(t_objlst obj)
{
	int			id;
	t_circle	c;

	id = obj.id;
	c = *((t_circle *)obj.obj);
	printf("  [%2d] circle { center=(%.4f,%.4f,%.4f), normal=(%.4f,%.4f,%.4f)"
		"r=%.4f, colr=[%d,%d,%d] }\n",
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

void	print_triangle(t_objlst obj)
{
	int			id;
	t_triangle	t;

	id = obj.id;
	t = *((t_triangle *)obj.obj);
	printf("  [%2d] triangle { a=(%.4f,%.4f,%.4f), b=(%.4f,%.4f,%.4f), "
		"c=(%.4f,%.4f,%.4f), colr=[%d,%d,%d] }\n",
		id,
		t.a.x,
		t.a.y,
		t.a.z,
		t.b.x,
		t.b.y,
		t.b.z,
		t.c.x,
		t.c.y,
		t.c.z,
		t.colr.r,
		t.colr.g,
		t.colr.b);
}
