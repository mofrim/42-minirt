/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:01:16 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/07 21:41:35 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	t_colr c = colr_add_colr(a, b);
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
	content = validate_file_content(argv[1]);
	if (!content)
		return (1);

	// FIXME: see comment on has_minimum_required_elements function
	//
	// if (!has_minimum_required_elements(content))
	// {
	// 	ft_putendl_fd("Error: Scene file must contain at least A, C, and L elements", 2);
	// 	free(content);
	// 	return (1);
	// }

	tokenizer = tokenizer_new(content);
	parser = parser_new(tokenizer);
	scene = parser_parse(parser);
	if (!scene)
	{
		ft_putendl_fd("Error: Failed to parse scene", 2);
		free(content);
		tokenizer_free(tokenizer);
		parser_free(parser);
		return (1);
	}
	tokenizer_free(tokenizer);
	parser_free(parser);
	debug_parsed_scene(scene);
	setup_scene(scene);
	mrt = init_mrt(scene);
	if (!mrt)
	{
		free(content);
		return (1);
	}

	// FIXME: Why is this working?
	// mlx_key_hook(mrt->win, kbd_input_handler, mrt);
	mlx_hook(mrt->win, KeyPress, KeyPressMask, kbd_input_handler, mrt);

	mlx_hook(mrt->win, DestroyNotify, 0, close_btn_handler, mrt);
	do_stuff(*mrt);
	mlx_loop(mrt->mlx);
	cleanup_mrt(mrt);
	free(content);

	return (0);
}
