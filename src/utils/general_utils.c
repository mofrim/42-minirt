/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:52:36 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/22 22:47:01 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Exit with error custom error msg, or not. */
void	error_exit(char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error\nFatal: ");
	if (msg)
		perror(msg);
	else
		perror("Fatal Error");
	exit(EXIT_FAILURE);
}

/* Convenience error printing to stderr. Prints "Error\n" followed by the msg
 * given as argument. */
void	print_errmsg(char *msg)
{
	if (!msg)
		return ;
	ft_dprintf(STDERR_FILENO, "Error\n-> %s\n", msg);
}

/* Convenience error printing to stderr. Prints "Error\n" followed by the msg
 * given as argument AND sets valid flag in tokenizer to false. */
void	printerr_set_invalid(char *msg, t_tokenizer *tok)
{
	if (!msg)
		return ;
	ft_dprintf(STDERR_FILENO, "Error\n-> %s\n", msg);
	tok->valid = false;
}

/* Print a errmsg to stderr, append a newline and exit with EXIT_FAILURE. */
void	exit_with_errmsg(char *msg)
{
	print_errmsg(msg);
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
