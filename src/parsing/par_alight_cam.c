/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_alight_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:17:05 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/19 01:42:44 by fmaurer          ###   ########.fr       */
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
// QUESTION: what to do with the valid flag??? should every parsing function
// carry the flag along? Should all the checking be done in the parsing
// functions or later in setup_scene (or a check_scene function before that??)?
t_amb_light	*parse_ambient_light(t_tokenizer *tokenizer)
{
	t_amb_light	*amb_light;
	bool valid;

	valid = true;
	amb_light = malloc(sizeof(t_amb_light));
	nullcheck(amb_light, "parse_ambient_light()");

	// FIXME: check for brightness value in range [0,1], otherwise: throw error
	amb_light->bright = parse_number(tokenizer);

	// FIXME: parse bright before colr and then add to colr as brightness
	amb_light->colr = parse_color(tokenizer, &valid);
	amb_light->colr.i = amb_light->bright;
	return (amb_light);
}

t_camera	*parse_camera(t_tokenizer *tokenizer)
{
	t_camera	*camera;
	bool valid;

	valid = true;
	camera = malloc(sizeof(t_camera));
	nullcheck(camera, "parse_camera");
	camera->pos = parse_v3(tokenizer, &valid);
	camera->orient = parse_v3(tokenizer, &valid);
	camera->fov = parse_number(tokenizer);
	return (camera);
}

