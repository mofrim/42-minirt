/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:08:06 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/17 22:30:08 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Helper function for parse_scene. */
static void	free_mrt_exit(t_mrt *mrt)
{
	free(mrt);
	exit(1);
}

static void	free_tok_rtfile(t_tokenizer *tok, char *scf)
{
	free(tok);
	free(scf);
}

void	cleanup_scene_mrt(t_mrt *mrt, t_scene *sc)
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

/* All the file reading and parsing is done in here. */
t_scene	*parse_scene(char *scene_filename, t_mrt *mrt)
{
	t_scene		*scene;
	t_tokenizer	*toknizr;
	char		*rtfile_content;

	if (!has_rt_ext(scene_filename))
	{
		print_errmsg("Invalid extension. Expected '.rt'");
		free_mrt_exit(mrt);
	}
	rtfile_content = read_scenefile(scene_filename);
	if (!rtfile_content)
		free_mrt_exit(mrt);
	toknizr = tokenizer_new(rtfile_content);
	scene = init_scene();
	if (lineparse_scenefile(toknizr, scene) == -1)
	{
		free_tok_rtfile(toknizr, rtfile_content);
		cleanup_scene_mrt(mrt, scene);
		exit_with_errmsg("Failed to parse scene");
	}
	free_tok_rtfile(toknizr, rtfile_content);
	setup_scene(scene);
	return (scene);
}
