/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_alight_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:17:05 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/23 14:09:57 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Ambient light parsing func.
 *
 * Expected Structure:
 * - alight's intensity aka brightness (float)
 * - alight's color (t_colr)
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

/**
 * Parse the camera.
 *
 * Structure:
 * - pos (t_v3)
 * - orientation (t_v3)
 * - field of view in degrees aka fov (float), with 0 < fov < 180
 */
t_camera	*parse_camera(t_tokenizer *tok)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	nullcheck(cam, "parse_camera");
	cam->pos = parse_v3(tok);
	cam->orient = parse_v3(tok);
	cam->fov = parse_pos_num(tok);
	if (cam->fov <= 0 || 180 <= cam->fov)
		printerr_set_invalid("cam fov not in range (0, 180)", &tok->valid);
	return (cam);
}
