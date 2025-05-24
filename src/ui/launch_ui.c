/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:34:50 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 20:21:50 by fmaurer          ###   ########.fr       */
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
	show_sidebar(mrt, true);
	print_scene(*mrt.scene);
	if (mrt.scene->alight && mrt.scene->cam)
	{
		printf("doing the 1st trace!\n");
		launch_raytrace(mrt);
		printf("done!\n");
	}
}
