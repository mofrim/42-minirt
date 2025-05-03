/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objlst_print_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:41:33 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/03 11:41:52 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_hyper(t_objlst obj)
{
	t_hyper	h;

	h = *((t_hyper *)obj.obj);
	printf("  [%2d] hyper { c=(%.4f,%.4f,%.4f), axis=(%.4f,%.4f,%.4f), "
		"a=%.4f, b=%.4f, h=%.4f, colr=[%d,%d,%d] }\n",
		obj.id,
		h.center.x,
		h.center.y,
		h.center.z,
		h.axis.x,
		h.axis.y,
		h.axis.z,
		h.a,
		h.b,
		h.h,
		h.colr.r,
		h.colr.g,
		h.colr.b);
}
