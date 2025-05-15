/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:34:50 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/15 10:56:47 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Small but important: draw our minirt to the window!
 *
 * Aka `do_stuff`.
 */
void	launch_ui(t_mrt mrt)
{
	show_sidebar(mrt);
	print_scene(*mrt.scene);
	if (mrt.scene->alight && mrt.scene->cam)
	{
		printf("doing the 1st trace!\n");
		raytrace_xpm(mrt);
		printf("done!\n");
	}
}
