/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_input_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:49:56 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/09 10:29:18 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keycodes.h"
#include "mlx_int.h"

void	handle_quit_destroy_keys(int key, t_mrt *mrt);
void	handle_subsample(int key, t_mrt mrt);
void	handle_fov(int key, t_mrt mrt);
void	handle_cam_rot_keys(int key, t_mrt mrt);
void	handle_cam_dir_keys(int key, t_mrt mrt);
void	handle_amb_bright(int key, t_mrt mrt);
void	handle_objlst_print(int key, t_mrt mrt);
void	handle_export(int key, t_mrt mrt);

static bool	is_autorep_key(int key)
{
	if (key == KEY_LCBRACE || key == KEY_RCBRACE || key == KEY_1 || \
key == KEY_9 || key == KEY_0 || key == KEY_EQUAL || key == KEY_MINUS || \
key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT || \
key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		return (true);
	return (false);
}

int	kbd_press_handler(int key, t_mrt *mrt)
{
	if (is_autorep_key(key))
	{
		mrt->autorep = true;
		mlx_do_key_autorepeaton(mrt->mlx);
	}
	if (!is_autorep_key(key) && key == mrt-> last_key && !mrt->autorep)
		return (0);
	handle_subsample(key, *mrt);
	handle_fov(key, *mrt);
	handle_cam_rot_keys(key, *mrt);
	handle_cam_dir_keys(key, *mrt);
	handle_amb_bright(key, *mrt);
	handle_quit_destroy_keys(key, mrt);
	handle_export(key, *mrt);
	handle_objlst_print(key, *mrt);
	return (0);
}

int	kbd_release_handler(int key, t_mrt *mrt)
{
	if (!is_autorep_key(key) && key != mrt->last_key)
	{
		mrt->autorep = false;
		mlx_do_key_autorepeatoff(mrt->mlx);
	}
	mrt->last_key = key;
	return (0);
}

/* Redraw window content after changes to scene have been made. */
void	redraw_win(t_mrt mrt)
{
	mlx_clear_window(mrt.mlx, mrt.win);
	show_sidebar(mrt);
	raytrace_xpm(mrt);
}

void	handle_quit_destroy_keys(int key, t_mrt *mrt)
{
	if (key == KEY_ESC)
	{
		cleanup_mrt(mrt);
		exit(0);
	}
}
