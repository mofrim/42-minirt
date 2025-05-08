/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_btn_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:48:30 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 10:06:05 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Cleanly exit the program when close button is clicked. */
int	close_btn_handler(t_mrt *mrt)
{
	printf("Close button clicked. Exiting.\n");
	cleanup_mrt(mrt);
	exit(0);
}
