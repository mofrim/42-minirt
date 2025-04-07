/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:18:34 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/07 22:33:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_rt(char *filename)
{
	size_t	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (filename[len - 3] != '.' || filename[len - 2] != 'r' || \
			filename[len - 1] != 't')
		return (false);
	return (true);
}

/* Basic scenefile validation. No allocs until here so using exit is fine. */
char	*validate_file_content(char *filename)
{
	char	*content;

	if (!is_rt(filename))
		exit_with_errmsg("Error\nInvalid extension. Expected '.rt'");
	content = read_file(filename);
	if (!content)
		exit_with_errmsg("Error\nFailed to read file");
	if (!*content)
	{
		free(content);
		exit_with_errmsg("Error\nFile is empty");
	}
	return (content);
}

static bool	is_colr_value(int value)
{
	return (value >= 0 && value <= 255);
}

// QUESTION where is this used?
// possible FIXME: is the error msg printing subject.pdf-conform?
t_colr	validate_color(t_colr color, bool *valid)
{
	if (!is_colr_value(color.r) || !is_colr_value(color.g) || \
			!is_colr_value(color.b))
	{
		ft_dprintf(STDERR_FILENO, "Error\nInvalid RGB values");
		*valid = false;
	}
	return (color);
}
