/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:32:55 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/03 11:31:52 by fmaurer          ###   ########.fr       */
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

/* Add 2 colrs. Avoid oveflow by maxing out to 255. */
t_colr	colr_add_colr(t_colr c1, t_colr c2)
{
	t_colr	res;

	res.r = (c1.r + c2.r > 255) * 255 + (c1.r + c2.r <= 255) \
			* (uint8_t)(c1.r + c2.r);
	res.g = (c1.g + c2.g > 255) * 255 + (c1.g + c2.g <= 255) \
			* (uint8_t)(c1.g + c2.g);
	res.b = (c1.b + c2.b > 255) * 255 + (c1.b + c2.b <= 255) \
			* (uint8_t)(c1.b + c2.b);
	return (res);
}

/**
 * Add the a spotlights influence to a pixel colr.
 *
 * The Blending is controlled via the spotlights brightness or intensity. If the
 * brightness is high the lights effect on overblending the objects original
 * color will be high.
 */
t_colr	colr_add_light(t_colr c, t_colr l, float light_intens)
{
	t_colr	res;

	res.r = (uint8_t)fmin(255, c.r * (1.0f - light_intens + \
				light_intens * l.r / 255.0f));
	res.g = (uint8_t)fmin(255, c.g * (1.0f - light_intens + \
				light_intens * l.g / 255.0f));
	res.b = (uint8_t)fmin(255, c.b * (1.0f - light_intens + \
				light_intens * l.b / 255.0f));
	return (res);
}

/* Another approach for adding the effect of the ambient light. The rationale
 * here:
 * 	- in the absence of any spotlights and an ambient light set to 0 we want to
 * 	end up with a black scene
 * 	- the final color value of the object should be limited in a way that if one
 * 	component reaches 255 the other won't get increased more
 *
 */
t_colr	colr_add_amblight(t_colr oc, t_colr ac, float abright)
{
	t_colr	res;

	res.r = (uint8_t)fmin(255, (oc.r + ac.r * abright) * abright);
	res.g = (uint8_t)fmin(255, (oc.g + ac.g * abright) * abright);
	res.b = (uint8_t)fmin(255, (oc.b + ac.b * abright) * abright);
	return (res);
}
//// another approach... keep for now.
//
// t_colr	colr_add_amblight(t_colr oc, t_colr ac, float abright)
// {
// 	t_colr	res;
//
// 	res.r = (uint8_t)fmin(255, oc.r * ac.r/255.0f * abright);
// 	res.g = (uint8_t)fmin(255, oc.g * ac.g/255.0f * abright);
// 	res.b = (uint8_t)fmin(255, oc.b * ac.b/255.0f * abright);
// 	return (res);
// }

/* Print a colr var and its name. */
void	colr_print(t_colr c, char *name)
{
	printf("colr-%s: [%d, %d, %d]\n", name, c.r, c.g, c.b);
}
