/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_handle_hq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:07:28 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 16:10:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_sidebar(t_mrt *mrt)
{
	mrt->side_thm = set_sidethm_black();
	show_sidebar(*mrt);
	mrt->side_thm = set_sidethm_default();
}

void	handle_supersample_ppx(int key, t_mrt *mrt)
{
	if (key == KEY_3)
	{
		clear_sidebar(mrt);
		mrt->scene->supersample = true;
		if (mrt->scene->samples_ppx >= 4)
		{
			mrt->scene->samples_ppx -= 2;
			mrt->scene->samples_ppx_half = mrt->scene->samples_ppx / 2;
		}
		show_sidebar(*mrt);
	}
	if (key == KEY_4)
	{
		clear_sidebar(mrt);
		mrt->scene->supersample = true;
		if (mrt->scene->samples_ppx <= 62)
		{
			mrt->scene->samples_ppx += 2;
			mrt->scene->samples_ppx_half = mrt->scene->samples_ppx / 2;
		}
		show_sidebar(*mrt);
	}
}

void	handle_supersample_step(int key, t_mrt *mrt)
{
	if (key == KEY_5)
	{
		clear_sidebar(mrt);
		mrt->scene->supersample = true;
		if (mrt->scene->sample_step >= 2)
			mrt->scene->sample_step--;
		show_sidebar(*mrt);
	}
	if (key == KEY_6)
	{
		clear_sidebar(mrt);
		mrt->scene->supersample = true;
		if (mrt->scene->sample_step <= 99)
			mrt->scene->sample_step++;
		show_sidebar(*mrt);
	}
}

void	handle_hq(int key, t_mrt *mrt)
{
	if (key == KEY_H)
	{
		mrt->scene->supersample = true;
		mlx_clear_window(mrt->mlx, mrt->win);
		show_sidebar(*mrt);
		mlx_string_put(mrt->mlx, mrt->win, WINX / 2 + 50, WINY / 2,
			rgb_to_int(GREEN), "supersampling the scene...");
		mlx_do_sync(mrt->mlx);
		if (BONUS)
		{
			ft_printf("\n-> supersampling using %d threads", THREADS);
			raytrace_hq_pthread(*mrt);
		}
		else
		{
			ft_printf("-> supersampling");
			raytrace_xpm_hq(*mrt);
		}
	}
}
