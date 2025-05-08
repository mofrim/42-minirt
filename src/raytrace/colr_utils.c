/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:32:55 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/08 09:51:46 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Simply add together 2 t_colrs channelwise.
 *
 * Use this in combination with colr_add_light.
 */
t_colr	colr_add_colr(t_colr c1, t_colr c2)
{
	t_colr	res;

	res.r = (c1.r + c2.r > 255) * 255 + (c1.r + c2.r <= 255)
		* (uint8_t)(c1.r + c2.r);
	res.g = (c1.g + c2.g > 255) * 255 + (c1.g + c2.g <= 255)
		* (uint8_t)(c1.g + c2.g);
	res.b = (c1.b + c2.b > 255) * 255 + (c1.b + c2.b <= 255)
		* (uint8_t)(c1.b + c2.b);
	res.i = c1.i;
	return (res);
}

/** Add a light effect to a objects color (oc).
 *
 * - If oc is zero in one channel -> no effect.
 * - If lights color is zero in one channel -> no effect.
 * - In between: only return the contribution of the light on the channel
 *   weighted by the surfaces refelctirvity (aka color) in that channel (the
 *   factor c.x/255.0) and by the lights intensity.
 */
t_colr	colr_add_light(t_colr c, t_colr l)
{
	t_colr	res;

	res.r = (uint8_t)fmin(255, (c.r / 255.0f) * l.i * l.r);
	res.g = (uint8_t)fmin(255, (c.g / 255.0f) * l.i * l.g);
	res.b = (uint8_t)fmin(255, (c.b / 255.0f) * l.i * l.b);
	res.i = c.i;
	return (res);
}

/**
 * Add ambient lights contribution to hitpoints colr.
 *
 * Well... after long struggle this the most promising solution. 1st, we limit
 * the ambient lights contribution to half the max intensity per channel this is
 * why we max out at 127. The reason is, we explicitly do not want overexposure
 * & we can do it like :) 2nd, the calculation here only uses ratios so if any
 * of the channels, either in the surface color (sc) or in the ambient light
 * (ac) is zero there is not contribution! This behavior implements the physical
 * property of an objects color: if it has a color in a certain channel it
 * reflects light in that channel proportionally to that colors value.
 * Similarly, if a light source has a certain value in one channel it will
 * lighten any object proportionally to that channels value.
 */
t_colr	hp_add_alight(t_colr sc, t_colr al)
{
	t_colr	res;

	res.r = (uint8_t)fmin(127, 127 * (sc.r / 255.0f) * (al.r / 255.0f) * al.i);
	res.g = (uint8_t)fmin(127, 127 * (sc.g / 255.0f) * (al.g / 255.0f) * al.i);
	res.b = (uint8_t)fmin(127, 127 * (sc.b / 255.0f) * (al.b / 255.0f) * al.i);
	return (res);
}

/* Add the contribution of a pointlight to the existing final color of a
 * hitpoint struct. */
t_colr	hp_add_pointlight(t_hp hp, t_colr light_colr)
{
	return (colr_add_colr(hp.fcolr, colr_add_light(hp.scolr, light_colr)));
}
