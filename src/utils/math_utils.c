/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:46:34 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 10:09:08 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Returns the radians to degree conversion of the input (which is expected to
 * be in radians, of course). Cuts off any not int portion. */
int	rad2deg_int(double rad)
{
	return ((int)(rad * 180 / M_PI));
}
