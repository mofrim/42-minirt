/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objlst_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:07:08 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/11 10:28:04 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_light(t_light l)
{
	printf("  light { pos=(%f,%f,%f), colr=(%d,%d,%d), intens=%f }\n",
		l.pos.x, l.pos.y, l.pos.z,
		l.colr.r, l.colr.g, l.colr.b, l.bright);
}

// TODO refac to use single func for spheres also
void	objlst_print(t_objlst *lst)
{
	while (lst)
	{
		if (lst->type == SPHERE)
		{
			printf("  sphere { center=(%f,%f,%f), r=%f, r**2=%f"
					" colr=[%d,%d,%d] }\n",
					((t_sphere *)lst->obj)->center.x,
					((t_sphere *)lst->obj)->center.y,
					((t_sphere *)lst->obj)->center.z,
					((t_sphere *)lst->obj)->r,
					((t_sphere *)lst->obj)->r_squared,
					((t_sphere *)lst->obj)->colr.r,
					((t_sphere *)lst->obj)->colr.g,
					((t_sphere *)lst->obj)->colr.b);
		}
		if (lst->type == LIGHT)
			print_light(*((t_light *)lst->obj));
		lst = lst->next;
	}
}
