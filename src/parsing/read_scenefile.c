/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scenefile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:18:34 by jroseiro          #+#    #+#             */
/*   Updated: 2025/05/08 09:50:34 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Basic scenefile validation. No allocs until here so using exit is fine. */
char	*read_scenefile(char *filename)
{
	char	*content;

	content = read_file(filename);
	if (!content)
		return (print_errmsg("failed to read file", NULL), NULL);
	if (!*content)
		return (free(content), print_errmsg("file is empty", NULL), NULL);
	return (content);
}

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

/* Extracted routine for appending fresh buffer to already read file content. */
static void	append_from_file(char **file_content, char *buf)
{
	char	*temp;

	temp = *file_content;
	*file_content = ft_strjoin(*file_content, buf);
	nullcheck(file_content, "read_file()");
	free(temp);
}

/* Read the scene file from path. */
char	*read_file(char *filename)
{
	int		fd;
	char	*buf;
	char	*file_content;
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	file_content = ft_strdup("");
	buf = ft_calloc(FILE_BUFSIZE, sizeof(char));
	nullcheck(buf, "read_file()");
	bytes_read = read(fd, buf, FILE_BUFSIZE);
	if (bytes_read == -1)
		return (free(buf), NULL);
	while (bytes_read > 0)
	{
		append_from_file(&file_content, buf);
		ft_bzero(buf, FILE_BUFSIZE);
		bytes_read = read(fd, buf, FILE_BUFSIZE);
		if (bytes_read == -1)
			return (free(buf), NULL);
	}
	close(fd);
	return (free(buf), file_content);
}
