/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 07:40:20 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/30 13:29:24 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keycodes.h"

void	handle_amb_bright(int key, t_mrt mrt)
{
	if (key == KEY_EQUAL && mrt.scene->alight->colr.i + 0.1 <= 1.0)
	{
		mrt.scene->alight->colr.i += 0.1;
		redraw_win(mrt);
	}
	if (key == KEY_MINUS && mrt.scene->alight->colr.i - 0.1 >= 0)
	{
		mrt.scene->alight->colr.i -= 0.1;
		redraw_win(mrt);
	}
}

void	handle_objlst_print(int key, t_mrt mrt)
{
	if (key == KEY_P)
	{
		printf("current objects:\n");
		objlst_print(mrt.scene->objects);
	}
}

void	handle_export(int key, t_mrt mrt)
{
	if (key == KEY_E)
	{
		ft_printf("exporting to scene.xpm");
		if (export_ppm(*mrt.xc) != -1)
			ft_printf(" done!\n");
	}
}
