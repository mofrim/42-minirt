/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_alight_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:17:05 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 12:57:07 by fmaurer          ###   ########.fr       */
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
t_colr	*parse_ambient_light(t_tokenizer *tok)
{
	t_colr	*alight;
	double	bright;

	alight = malloc(sizeof(t_colr));
	bright = parse_pos_num(tok);
	if (bright > 1.0)
		printerr_set_invalid("ambient light bright incorrect", &tok->valid);
	if (tok->valid)
	{
		*alight = parse_color(tok);
		alight->i = bright;
	}
	return (alight);
}

/**
 * Parse a point light source.
 *
 * Expected Structure:
 * - pos (t_v3)
 * - brightness (float)
 * - color (t_colr)
 *
 * Example: "L 0,0,0 0.5 255,255,255"
 * Rules: 0 <= bright <= 1.0
 */
t_light	*parse_light(t_tokenizer *tok)
{
	t_light	*light;
	float	bright;

	light = malloc(sizeof(t_light));
	nullcheck(light, "parse_light()");
	light->pos = parse_v3(tok);
	bright = parse_pos_num(tok);
	if (bright > 1.0)
		printerr_set_invalid("pointlight too bright", &tok->valid);
	light->colr = parse_color(tok);
	light->colr.i = bright;
	return (light);
}

/**
 * Parse the camera.
 *
 * Expected Structure:
 * - pos (t_v3)
 * - orientation (t_v3)
 * - field (float)
 *
 * Example:	"C 0,0,1 0,0,-1 70"
 * Rules:	|orient| > 0, 0 < fov < 180
 */
t_camera	*parse_camera(t_tokenizer *tok)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	nullcheck(cam, "parse_camera");
	cam->pos = parse_v3(tok);
	cam->orient = parse_v3(tok);
	cam->fov = parse_pos_num(tok);
	if (v3_norm(cam->orient) == 0)
		printerr_set_invalid("cam orient norm == 0", &tok->valid);
	if (cam->fov <= 0 || 180 <= cam->fov)
		printerr_set_invalid("cam fov not in range (0, 180)", &tok->valid);
	cam->fov = cam->fov * M_PI / 180.0;
	cam->orient = v3_normalize(cam->orient);
	cam->rot = get_rotmtrx(cam->orient);
	cam->view_width = 2 * EPS * tan(cam->fov / 2);
	cam->cvr = cam->view_width / CANVAS_WIDTH;
	return (cam);
}
