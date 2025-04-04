/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:52:36 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/22 16:24:48 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Exit with error custom error msg, or not. */
void	error_exit(char *msg)
{
	if (msg)
		perror(msg);
	else
		perror("Error");
	exit(EXIT_FAILURE);
}

/* Perform NULL check on pointer. error_exit with msg if NULL. */
void	nullcheck(void *p, char *msg)
{
	if (!p)
		error_exit(msg);
}

char *read_file(char *filename)
{
	int fd;
	char *line;
	char *temp;
	char *file_content;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening scene file");
		return (NULL);
	}
	file_content = ft_strdup("");
	if (!file_content)
	{
		close(fd);
		return (NULL);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		temp = file_content;
		file_content = ft_strjoin(file_content, line);
		free(temp);
		free(line);
		if (!file_content)
		{
			close(fd);
			return (NULL);
		}
	}
	close(fd);
	return (file_content);
}
