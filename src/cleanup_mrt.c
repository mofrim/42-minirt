/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_mrt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:11:23 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 10:17:44 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Cleanup for clean program exit. */
void	cleanup_mrt(t_mrt *mrt)
{
	mlx_destroy_image(mrt->mlx, mrt->xc->img);
	mlx_destroy_window(mrt->mlx, mrt->win);
	mlx_destroy_display(mrt->mlx);
	free(mrt->xc);
	free(mrt->mlx);
	objlst_clear(*mrt, mrt->scene->objects);
	free(mrt->scene->cam);
	free(mrt->scene->alight);
	free(mrt->scene);
	free(mrt);
}
