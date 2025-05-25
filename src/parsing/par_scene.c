/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:08:06 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/25 20:23:32 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	cleanup_scene_mrt(t_mrt *mrt, t_scene *sc);
static void	free_mrt_exit(t_mrt *mrt);

/**
 * Main scenefile parsing func.
 *
 * Reads the file content and tries to parse the scene file linewise. If any
 * errors occur, frees ressources & exits the program immediately
 */
t_scene	*parse_scene(char *scene_filename, t_mrt *mrt)
{
	t_scene		*scene;
	char		*rtfile_content;

	if (!has_rt_ext(scene_filename))
	{
		print_errmsg("invalid file extension. Expected '.rt'", NULL);
		free_mrt_exit(mrt);
	}
	rtfile_content = read_scenefile(scene_filename);
	if (!rtfile_content)
		free_mrt_exit(mrt);
	scene = init_scene();
	if (lineparse_scenefile(rtfile_content, scene) == -1)
	{
		free(rtfile_content);
		cleanup_scene_mrt(mrt, scene);
		exit_with_errmsg("failed to parse scene");
	}
	free(rtfile_content);
	return (scene);
}

/* Helper function for parse_scene. */
static void	free_mrt_exit(t_mrt *mrt)
{
	free(mrt);
	exit(1);
}

/* Cleanup subroutine if parsing fails at some line in scenefile.  */
static void	cleanup_scene_mrt(t_mrt *mrt, t_scene *sc)
{
	if (sc->objects)
		objlst_clear(sc->objects);
	if (sc->cam)
		free(sc->cam);
	if (sc->alight)
		free(sc->alight);
	free(sc);
	free(mrt);
}
