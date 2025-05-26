/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_handle_hq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:07:28 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/26 21:13:44 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_supersample_ppx(int key, t_mrt *mrt)
{
	if (key == KEY_3)
	{
		mrt->scene->supersample = true;
		if (mrt->scene->samples_ppx >= 4)
		{
			mrt->scene->samples_ppx -= 2;
			mrt->scene->samples_ppx_half = mrt->scene->samples_ppx / 2;
		}
		if (mrt->show_sidebar)
			update_sidebar(mrt);
	}
	if (key == KEY_4)
	{
		mrt->scene->supersample = true;
		if (mrt->scene->samples_ppx <= 62)
		{
			mrt->scene->samples_ppx += 2;
			mrt->scene->samples_ppx_half = mrt->scene->samples_ppx / 2;
		}
		if (mrt->show_sidebar)
			update_sidebar(mrt);
	}
}

void	handle_supersample_step(int key, t_mrt *mrt)
{
	if (key == KEY_5)
	{
		mrt->scene->supersample = true;
		if (mrt->scene->sample_step >= 2)
			mrt->scene->sample_step--;
		if (mrt->show_sidebar)
			update_sidebar(mrt);
	}
	if (key == KEY_6)
	{
		mrt->scene->supersample = true;
		if (mrt->scene->sample_step <= 99)
			mrt->scene->sample_step++;
		if (mrt->show_sidebar)
			update_sidebar(mrt);
	}
}

void	handle_hq(int key, t_mrt *mrt)
{
	if (key == KEY_H)
	{
		mrt->scene->supersample = true;
		if (mrt->show_sidebar)
			update_sidebar(mrt);
		put_string_canvas(*mrt, (t_pxl){-50, 0}, GREEN,
			"supersampling scene...");
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
