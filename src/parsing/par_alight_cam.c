/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_alight_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:17:05 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/23 10:48:18 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TODO add checking functions in here!

/**
 * Ambient light parsing func.
 *
 * Expected Structure:
 * - alight's intensity aka brightness
 * - alight's color
 *
 * Example: "A 0.3 255,255,255"
 * Rules: 0 <= bright <= 1, colr must be valid
 */
t_alight	*parse_ambient_light(t_tokenizer *tok)
{
	t_alight	*alight;

	alight = malloc(sizeof(t_alight));
	nullcheck(alight, "parse_ambient_light()");
	alight->bright = parse_pos_num(tok);
	if (alight->bright > 1.0)
		printerr_set_invalid("ambient light too bright", &tok->valid);
	alight->colr = parse_color(tok);
	alight->colr.i = alight->bright;
	return (alight);
}

t_camera	*parse_camera(t_tokenizer *tok)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	nullcheck(camera, "parse_camera");
	camera->pos = parse_v3(tok);
	camera->orient = parse_v3(tok);
	camera->fov = parse_pos_num(tok);
	return (camera);
}
