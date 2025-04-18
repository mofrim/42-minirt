/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:18:34 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/18 11:03:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Check if scene file ends with '.rt' */
bool	has_rt_ext(char *filename)
{
	size_t	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 3)
		return (false);
	if (filename[len - 3] != '.' || filename[len - 2] != 'r' || \
			filename[len - 1] != 't')
		return (false);
	return (true);
}

/* Basic scenefile validation. No allocs until here so using exit is fine. */
char	*read_scenefile(char *filename)
{
	char	*content;

	content = read_file(filename);
	if (!content)
		return (print_errmsg("Failed to read file"), NULL);
	if (!*content)
		return (free(content), print_errmsg("File is empty"), NULL);
	return (content);
}
