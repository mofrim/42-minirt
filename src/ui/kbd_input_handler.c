/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_input_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:49:56 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/30 13:47:52 by fmaurer          ###   ########.fr       */
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

int	kbd_input_handler(int key, t_mrt *mrt)
{
	handle_quit_destroy_keys(key, mrt);
	handle_subsample(key, *mrt);
	handle_fov(key, *mrt);
	handle_cam_rot_keys(key, *mrt);
	handle_cam_dir_keys(key, *mrt);
	handle_amb_bright(key, *mrt);
	handle_objlst_print(key, *mrt);
	handle_export(key, *mrt);
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
