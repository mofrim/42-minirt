/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:01:16 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/09 11:01:38 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_mrt	*mrt;

	if (ac != 2)
		exit_with_errmsg("Error\nUsage: ./miniRT <scene.rt>");
	mrt = init_mrt(av[1]);
	mlx_hook(mrt->win, KeyPress, KeyPressMask, kbd_press_handler, mrt);
	mlx_hook(mrt->win, KeyRelease, KeyReleaseMask, kbd_release_handler, mrt);
	mlx_hook(mrt->win, DestroyNotify, 0, close_btn_handler, mrt);
	launch_ui(*mrt);
	mlx_loop(mrt->mlx);
	cleanup_mrt(mrt);
	return (0);
}
