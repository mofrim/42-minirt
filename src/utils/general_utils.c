/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:52:36 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/11 22:10:20 by fmaurer          ###   ########.fr       */
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

/* Print a errmsg to stderr, append a newline and exit with EXIT_FAILURE. */
void	exit_with_errmsg(char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s\n", msg);
	exit(EXIT_FAILURE);
}

/* Perform NULL check on pointer. error_exit with msg if NULL. */
void	nullcheck(void *p, char *msg)
{
	if (!p)
		error_exit(msg);
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

// FIXME: this is not necessary i would argue. the only thing i would say we can
// demand that a valid scene should have is a camera. but not even this i would
// be sure about. what is wrong with a scene file that only defines a sphere. or
// a light. or a camera? in principle nothing.

// bool has_minimum_required_elements(char *content)
// {
// 	bool has_ambient = false;
// 	bool has_camera = false;
// 	bool has_light = false;
// 	char **lines;
// 	int i;
//
// 	lines = ft_split(content, '\n');
// 	if (!lines)
// 		return (false);
// 	i = 0;
// 	while (lines[i])
// 	{
// 		// Skip whitespace at beginning of line
// 		char *trimmed = lines[i];
// 		while (*trimmed && ft_isspace(*trimmed))
// 			trimmed++;
// 		// Check for element identifiers
// 		if (*trimmed == 'A')
// 			has_ambient = true;
// 		else if (*trimmed == 'C')
// 			has_camera = true;
// 		else if (*trimmed == 'L')
// 			has_light = true;
// 		i++;
// 	}
// 	free_parts(lines);
// 	return (has_ambient && has_camera && has_light);
// }
