/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colr_base_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:47:50 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/22 14:09:56 by fmaurer          ###   ########.fr       */
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

static uint8_t	min3(uint8_t x, uint8_t y, uint8_t z)
{
	if (x != 0 && (x < y || y == 0) && (x < z || z == 0))
		return (x);
	if (y != 0 && (y < x || x == 0) && (y < z || z == 0))
		return (y);
	return (z);
}

/* Get a darker version of the color c. */
t_colr	colr_get_darker(t_colr c)
{
	float	min;

	min = min3(c.r, c.g, c.b) - 1;
	if (min <= 0)
		min = 1;
	c.r = (uint8_t)(c.r * 0.4);
	c.g = (uint8_t)(c.g * 0.4);
	c.b = (uint8_t)(c.b * 0.4);
	c.i = 1.0;
	return (c);
}

/* Get brightest version of a color c. Kind of... */
t_colr	colr_get_brightest(t_colr c)
{
	float	max;
	float	factor;
	int		tmp[3];

	max = fmaxf(c.r, fmaxf(c.g, c.b));
	if (max <= 0)
		max = 1;
	factor = 255 / max;
	tmp[0] = c.r * factor;
	tmp[1] = c.g * factor;
	tmp[2] = c.b * factor;
	c.r = tmp[0] * (tmp[0] <= 255) + 255 * (tmp[0] > 255);
	c.g = tmp[1] * (tmp[1] <= 255) + 255 * (tmp[1] > 255);
	c.b = tmp[2] * (tmp[2] <= 255) + 255 * (tmp[2] > 255);
	c.i = 1.0;
	return (c);
}
