/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colr_base_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:47:50 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/17 08:50:48 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Multiply a colr by a double value. Avoid oveflow by maxing out to 255. */
t_colr	colr_mult(t_colr c, double i)
{
	t_colr	res;

	res.r = (c.r * i > 255) * 255 + (c.r * i <= 255) * (uint8_t)(c.r * i);
	res.g = (c.g * i > 255) * 255 + (c.g * i <= 255) * (uint8_t)(c.g * i);
	res.b = (c.b * i > 255) * 255 + (c.b * i <= 255) * (uint8_t)(c.b * i);
	return (res);
}

/* Print a colr var and its name. */
void	colr_print(t_colr c, char *name)
{
	printf("colr-%s: [%d, %d, %d]\n", name, c.r, c.g, c.b);
}

/* Returns the colr multiplied by its intensity. */
t_colr	colr_apply_intns(t_colr c)
{
	c.r = (uint8_t)fmin(255, c.r * c.i);
	c.g = (uint8_t)fmin(255, c.g * c.i);
	c.b = (uint8_t)fmin(255, c.b * c.i);
	return (c);
}

static uint8_t	min3(uint8_t x, uint8_t y, uint8_t z)
{
	if (x != 0 && (x < y || y == 0) && (x < z || z == 0))
		return (x);
	if (y != 0 && (y < x || x == 0) && (y < z || z == 0))
		return (y);
	return (z);
}

/* Get the darkest possible version of the color c. */
t_colr	colr_get_darkest(t_colr c)
{
	float	min;

	min = min3(c.r, c.g, c.b) - 1;
	if (min < 0)
		min = 0;
	c.r = (uint8_t)(c.r * 1 / min);
	c.g = (uint8_t)(c.g * 1 / min);
	c.b = (uint8_t)(c.b * 1 / min);
	c.i = 1.0;
	return (c);
}
