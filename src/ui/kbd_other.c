/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 07:40:20 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/10 13:32:16 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keycodes.h"

void	handle_amb_bright(int key, t_mrt mrt)
{
	if (key == KEY_R && mrt.scene->alight->colr.i + 0.1 <= 1.0)
	{
		mrt.scene->alight->colr.i += 0.1;
		redraw_win(mrt);
	}
	if (key == KEY_T && mrt.scene->alight->colr.i - 0.1 >= 0)
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
