/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:01:16 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/03 09:59:49 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int key_press_handler(int key, t_mrt *mrt)
{
	(void)mrt;
	printf("key %d is pressed", key);
	return (0);
}

int	main(int ac, char **av)
{
	t_mrt		*mrt;
	t_scene		*scene;
	t_tokenizer *tokenizer;
	t_parser 	*parser;
	char 		*file_content;
	int 		fd;

	if (ac != 2)
		return (printf("Usage: ./minirt SCENE_FILE\n"), 1);

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error openingt scene file");
		return (1);
	}

	file_content = read_file(av[1]);
	if (!file_content)
		return (1);

	// Create a tokenizer with the scene file content
	tokenizer = tokenizer_new(file_content); // Pass the scene file path to tokenizer_new
	if (!tokenizer)
		return (printf("Error creating tokenizer\n"), 1);

	// Create a parser with the tokenizer
	parser = parser_new(tokenizer);
	if (!parser)
		return (printf("Error creating parser\n"), 1);

	// Parse the scene using the parser
	scene = parser_parse(parser);
	if (!scene)
		return (printf("Error during scene file parsing\n"), 1);

	tokenizer_free(tokenizer);
	parser_free(parser);
	// Debug the parsed scene
	debug_parsed_scene(scene);
	setup_scene(scene);
	mrt = init_mrt(scene);

	// FIXME: Why is this working?
	// mlx_key_hook(mrt->win, kbd_input_handler, mrt);
	mlx_hook(mrt->win, KeyPress, KeyPressMask, kbd_input_handler, mrt);

	mlx_hook(mrt->win, DestroyNotify, 0, close_btn_handler, mrt);
	do_stuff(*mrt);
	mlx_loop(mrt->mlx);
	cleanup_mrt(mrt);
	return (0);
}


// Helper function to read file content



// int	main(void)
// {
// 	t_colr a = {42, 42, 42};
// 	t_colr b = {0,0,100};
// 	t_colr c = colr_add_light(a, b);
// 	colr_print(c, "c");
//
// 	return (0);
// }
