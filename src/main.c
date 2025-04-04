/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:01:16 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/04 11:46:11 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int key_press_handler(int key, t_mrt *mrt)
// {
// 	(void)mrt;
// 	printf("key %d is pressed", key);
// 	return (0);
// }

// int	main(int ac, char **av)
// {
// 	t_mrt		*mrt;
// 	t_scene		*scene;
// 	t_tokenizer *tokenizer;
// 	t_parser 	*parser;
// 	char 		*file_content;
// 	int 		fd;

// 	if (ac != 2)
// 		return (printf("Usage: ./minirt SCENE_FILE\n"), 1);

// 	fd = open(av[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error openingt scene file");
// 		return (1);
// 	}

// 	file_content = read_file(av[1]);
// 	if (!file_content)
// 		return (1);

// 	// Create a tokenizer with the scene file content
// 	tokenizer = tokenizer_new(file_content); // Pass the scene file path to tokenizer_new
// 	if (!tokenizer)
// 		return (printf("Error creating tokenizer\n"), 1);

// 	// Create a parser with the tokenizer
// 	parser = parser_new(tokenizer);
// 	if (!parser)
// 		return (printf("Error creating parser\n"), 1);

// 	// Parse the scene using the parser
// 	scene = parser_parse(parser);
// 	if (!scene)
// 		return (printf("Error during scene file parsing\n"), 1);

// 	tokenizer_free(tokenizer);
// 	parser_free(parser);
// 	// Debug the parsed scene
// 	debug_parsed_scene(scene);
// 	setup_scene(scene);
// 	mrt = init_mrt(scene);
// 	mlx_key_hook(mrt->win, kbd_input_handler, mrt);

// 	// FIXME: Why is this working?
// 	mlx_hook(mrt->win, KeyPress, KeyPressMask, key_press_handler, mrt);

// 	mlx_hook(mrt->win, DestroyNotify, 0, close_btn_handler, mrt);
// 	do_stuff(*mrt);
// 	mlx_loop(mrt->mlx);
// 	cleanup_mrt(mrt);
// 	return (0);
// }


// // Helper function to read file content



// // int	main(void)
// // {
// // 	t_colr a = {42, 42, 42};
// // 	t_colr b = {0,0,100};
// // 	t_colr c = colr_add_light(a, b);
// // 	colr_print(c, "c");
// //
// // 	return (0);
// // }


/* Handler for key press events */
int key_press_handler(int key, t_mrt *mrt)
{
	(void)mrt;
	printf("key %d is pressed", key);
	return (0);
}

/* Function to test color operations if needed */
void test_colors(void)
{
	t_colr a = {42, 42, 42};
	t_colr b = {0, 0, 100};
	t_colr c = colr_add_light(a, b);
	colr_print(c, "c");
}

int	main(int argc, char **argv)
{
	t_mrt		*mrt;
	t_scene		*scene;
	t_tokenizer *tokenizer;
	t_parser 	*parser;
	char 		*content;

	if (argc != 2)
	{
		ft_putendl_fd("Error: Usage: ./miniRT <scene.rt>", 2);
		return (1);
	}

	// Validate file extension and content
	content = validate_file_content(argv[1]);
	if (!content)
		return (1);

	// Check for minimum required elements
	if (!has_minimum_required_elements(content))
	{
		ft_putendl_fd("Error: Scene file must contain at least A, C, and L elements", 2);
		free(content);
		return (1);
	}

	// Create tokenizer and parser
	tokenizer = tokenizer_new(content);
	if (!tokenizer)
	{
		ft_putendl_fd("Error: Failed to create tokenizer", 2);
		free(content);
		return (1);
	}

	parser = parser_new(tokenizer);
	if (!parser)
	{
		ft_putendl_fd("Error: Failed to create parser", 2);
		free(content);
		tokenizer_free(tokenizer);
		return (1);
	}

	// Parse the scene
	scene = parser_parse(parser);
	if (!scene)
	{
		ft_putendl_fd("Error: Failed to parse scene", 2);
		free(content);
		tokenizer_free(tokenizer);
		parser_free(parser);
		return (1);
	}

	// Free parser and tokenizer as they're no longer needed
	tokenizer_free(tokenizer);
	parser_free(parser);

	// Debug and set up scene
	debug_parsed_scene(scene);
	setup_scene(scene);

	// Initialize MiniRT
	mrt = init_mrt(scene);
	if (!mrt)
	{
		free(content);
		// Free scene resources here
		return (1);
	}

	// Set up event handlers
	mlx_key_hook(mrt->win, kbd_input_handler, mrt);
	mlx_hook(mrt->win, KeyPress, KeyPressMask, key_press_handler, mrt);
	mlx_hook(mrt->win, DestroyNotify, 0, close_btn_handler, mrt);

	// Do raytracing and display
	do_stuff(*mrt);
	
	// Start main loop
	mlx_loop(mrt->mlx);

	// Clean up (this code will only be reached if mlx_loop exits)
	cleanup_mrt(mrt);
	free(content);
	
	return (0);
}