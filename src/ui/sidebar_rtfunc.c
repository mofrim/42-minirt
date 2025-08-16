/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar_rtfunc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:09:14 by fmaurer           #+#    #+#             */
/*   Updated: 2025/08/17 00:24:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ui.h"

void	print_menu_text(t_mrt mrt, int x, int y, char *txt);

void	print_rtfunc(t_mrt mrt, int *i)
{
	if (mrt.rtfunc == RT_PXPUT)
		print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "rtfunc: pxput");
	else if (mrt.rtfunc == RT_XPM)
		print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "rtfunc: xpm");
	else if (mrt.rtfunc == RT_PTHREAD_PXPUT)
		print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "rtfunc: pthread_pxput");
	else
		print_menu_text(mrt, 30, 20 + (++(*i)) * 15, "rtfunc: pthread_xpm");
}
