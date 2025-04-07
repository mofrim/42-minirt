/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:01:16 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/08 00:40:36 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_mrt		*mrt;

	if (ac != 2)
		exit_with_errmsg("Error: Usage: ./miniRT <scene.rt>");
	mrt = init_mrt(av[1]);

	// FIXME: Make seperate key handlers for keys that should use autorepeat and
	// for those who shouldn't.
	//
	// mlx_key_hook(mrt->win, kbd_input_handler, mrt);
	mlx_hook(mrt->win, KeyPress, KeyPressMask, kbd_input_handler, mrt);

	mlx_hook(mrt->win, DestroyNotify, 0, close_btn_handler, mrt);
	do_stuff(*mrt);
	mlx_loop(mrt->mlx);
	cleanup_mrt(mrt);
	return (0);
}
