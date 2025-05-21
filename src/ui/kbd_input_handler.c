/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_input_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:49:56 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/21 08:13:53 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keycodes.h"

void	handle_quit_destroy_keys(int key, t_mrt *mrt);
void	handle_subsample(int key, t_mrt mrt);
void	handle_fov(int key, t_mrt mrt);
void	handle_cam_rot_keys(int key, t_mrt mrt);
void	handle_cam_dir_keys(int key, t_mrt mrt);
void	handle_amb_bright(int key, t_mrt mrt);
void	handle_objlst_print(int key, t_mrt mrt);
void	handle_export(int key, t_mrt mrt);
void	handle_hq(int key, t_mrt *mrt);
void	handle_supersample_ppx(int key, t_mrt *mrt);
void	handle_supersample_step(int key, t_mrt *mrt);
void	handle_rtfunc(int key, t_mrt *mrt);
void	handle_bump_nmap(int key, t_mrt *mrt);

/* This function checks if the key pressed is one where autorepeat should be
 * enabled for. */
static bool	is_autorep_key(int key)
{
	if (key == KEY_LCBRACE || key == KEY_RCBRACE || key == KEY_1 || \
key == KEY_9 || key == KEY_0 || key == KEY_EQUAL || key == KEY_MINUS || \
key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT || \
key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D || \
key == KEY_2 || key == KEY_3 || key == KEY_4 || key == KEY_5 || \
key == KEY_B || key == KEY_N)
		return (true);
	return (false);
}

/* All the UI key handlers. */
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
	handle_hq(key, mrt);
	handle_supersample_ppx(key, mrt);
	handle_supersample_step(key, mrt);
	handle_rtfunc(key, mrt);
	handle_bump_nmap(key, mrt);
	return (0);
}

/**
 * Hacky kbd release handler.
 *
 * Why? We wanted some keys to be auto-repeatable, f.ex. the keys for moving
 * around in the scene. Other keys like the export key should not be
 * auto-repeatable (only for UX reasons, which means, for saving the users from
 * themselves ;) The problem is: when auto-repeat is activated one might think
 * that just setting autorepeat off in a handler for a key that should not be
 * autorepeatable would suffice. But, for some deeper X11 reasons, the
 * autorepeatoff flag is not set before you lift the finger again once from the
 * key. That means, for the first time you hold down a no-autorepeat key it will
 * auto-repeat and only after release the key the autorepeatoff flag will be
 * set. This is very disappointing. So we made up this hacky system for ensuring
 * that non-autorep funcs won't get executed a 2nd time in a row.
 */
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
void	redraw_win(t_mrt mrt, bool print_msg)
{
	mlx_clear_window(mrt.mlx, mrt.win);
	show_sidebar(mrt);
	if (print_msg)
	{
		mlx_string_put(mrt.mlx, mrt.win, WINX / 2 + 50, WINY / 2,
			rgb_to_int(GREEN), "tracing rays...");
		mlx_do_sync(mrt.mlx);
	}
	launch_raytrace(mrt);
}

void	handle_quit_destroy_keys(int key, t_mrt *mrt)
{
	if (key == KEY_ESC)
	{
		cleanup_mrt(mrt);
		exit(0);
	}
}
