/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:08:06 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/23 10:21:18 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	cleanup_scene_mrt(t_mrt *mrt, t_scene *sc);
static void	free_mrt_exit(t_mrt *mrt);
static void	free_tok_rtfile(t_tokenizer *tok, char *scf);

/**
 * Main scenefile parsing func.
 *
 * Reads the file content and tries to parse the scene file linewise. If any
 * errors occur, frees ressources & exits the program immediately
 */
t_scene	*parse_scene(char *scene_filename, t_mrt *mrt)
{
	t_scene		*scene;
	t_tokenizer	*toknizr;
	char		*rtfile_content;

	if (!has_rt_ext(scene_filename))
	{
		print_errmsg("invalid file extension. Expected '.rt'", NULL);
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
		exit_with_errmsg("failed to parse scene");
	}
	free_tok_rtfile(toknizr, rtfile_content);
	setup_scene(scene);
	return (scene);
}

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
