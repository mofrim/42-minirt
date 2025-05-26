/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 07:40:20 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/26 21:12:23 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keycodes.h"

void	handle_amb_bright(int key, t_mrt *mrt)
{
	if (key == KEY_EQUAL)
	{
		if (mrt->scene->alight->i + 0.1 <= 1.0)
			mrt->scene->alight->i += 0.1;
		else
			mrt->scene->alight->i = 1.0;
		redraw_win(mrt, false);
	}
	if (key == KEY_MINUS)
	{
		if (mrt->scene->alight->i - 0.1 >= 0)
			mrt->scene->alight->i -= 0.1;
		else
			mrt->scene->alight->i = 0;
		redraw_win(mrt, false);
	}
}

void	handle_objlst_print(int key, t_mrt mrt)
{
	if (key == KEY_P)
		print_scene(*mrt.scene);
}

void	handle_export(int key, t_mrt *mrt)
{
	if (key == KEY_O)
	{
		ft_printf("exporting to scene.ppm");
		put_string_canvas(*mrt, (t_pxl){-70, -200}, GREEN,
			"exporting to scene.ppm...");
		mlx_do_sync(mrt->mlx);
		if (export_ppm(*mrt->xc, mrt->can_params.canvas_width) != -1)
			ft_printf(" done!\n");
		redraw_win(mrt, false);
	}
}

void	handle_rtfunc(int key, t_mrt *mrt)
{
	if (key == KEY_Z)
	{
		printf("-> changing rtfunc to raytrace.\n");
		mrt->rtfunc = RT_PXPUT;
	}
	if (key == KEY_X)
	{
		printf("-> changing rtfunc to raytrace_xpm.\n");
		mrt->rtfunc = RT_XPM;
	}
	if (THREADS > 1 && key == KEY_C)
	{
		printf("-> changing rtfunc to raytrace_pthread_xpm.\n");
		mrt->rtfunc = RT_PTHREAD_XPM;
	}
	if (THREADS > 1 && key == KEY_V)
	{
		printf("-> changing rtfunc to raytrace_pthread_pxput.\n");
		mrt->rtfunc = RT_PTHREAD_PXPUT;
	}
}

void	handle_bump_nmap(int key, t_mrt *mrt)
{
	if (key == KEY_B)
	{
		mrt->scene->bump = !mrt->scene->bump;
		redraw_win(mrt, false);
	}
	if (key == KEY_N)
	{
		mrt->scene->nmap = !mrt->scene->nmap;
		redraw_win(mrt, false);
	}
}
