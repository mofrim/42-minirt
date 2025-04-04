/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:18:34 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/04 11:29:33 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_rt(char *filename)
{
	size_t	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (filename[len - 3] != '.' || filename[len - 2] != 'r' || filename[len - 1] != 't')
		return (false);
	return (true);
}

char	*validate_file_content(char *filename)
{
	char *content;
	
	if (!is_rt(filename))
	{
		ft_putendl_fd("Error: Invalid extension. Expected '.rt'", 2);
		return (NULL);
	}
	
	content = read_file(filename);
	if (!content)
	{
		ft_putendl_fd("Error: Failed to read file", 2);
		return (NULL);
	}
	
	if (!*content)
	{
		ft_putendl_fd("Error: File is empty", 2);
		free(content);
		return (NULL);
	}
	
	return (content);
}

static bool	is_colr_value(int value)
{
	return (value >= 0 && value <= 255);
}

t_colr validate_color(t_colr color, bool *valid)
{
	if (!is_colr_value(color.r) ||
	 	!is_colr_value(color.g) ||
	 	!is_colr_value(color.b))
	{
		ft_putendl_fd("Error: Invalid RGB values", 2);
		*valid = false;
	}
	return (color);
}
