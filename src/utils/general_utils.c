/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:52:36 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/04 11:27:55 by zrz              ###   ########.fr       */
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

// char *read_file(char *filename)
// {
// 	int fd;
// 	char *line;
// 	char *temp;
// 	char *file_content;

// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening scene file");
// 		return (NULL);
// 	}
// 	file_content = ft_strdup("");
// 	if (!file_content)
// 	{
// 		close(fd);
// 		return (NULL);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		temp = file_content;
// 		file_content = ft_strjoin(file_content, line);
// 		free(temp);
// 		free(line);
// 		if (!file_content)
// 		{
// 			close(fd);
// 			return (NULL);
// 		}
// 	}
// 	close(fd);
// 	return (file_content);
// }


char *read_file(char *filename)
{
	int fd;
	char *buf;
	char *temp;
	char *file_content;
	int	bufsize = 1000;
	int	bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening scene file");
		return (NULL);
	}
	file_content = ft_strdup("");
	buf = malloc(sizeof(char) * bufsize);
	ft_bzero(buf, bufsize);
	nullcheck(buf, "read_file()");
	bytes_read = read(fd, buf, bufsize);
	if (bytes_read == -1)
		return (NULL);
	while (bytes_read > 0)
	{
		temp = file_content;
		file_content = ft_strjoin(file_content, buf);
		free(temp);
		ft_bzero(buf, bufsize);
		bytes_read = read(fd, buf, bufsize);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break;
	}
	if (!file_content)
		nullcheck(file_content, "read_file()");
	close(fd);
	ft_printf("%s", file_content);
	return (file_content);
}

bool has_minimum_required_elements(char *content)
{
    bool has_ambient = false;
    bool has_camera = false;
    bool has_light = false;
    char **lines;
    int i;
    
    lines = ft_split(content, '\n');
    if (!lines)
        return (false);
    
    i = 0;
    while (lines[i])
    {
        // Skip whitespace at beginning of line
        char *trimmed = lines[i];
        while (*trimmed && ft_isspace(*trimmed))
            trimmed++;
        
        // Check for element identifiers
        if (*trimmed == 'A')
            has_ambient = true;
        else if (*trimmed == 'C')
            has_camera = true;
        else if (*trimmed == 'L')
            has_light = true;
        
        i++;
    }
    
    free_parts(lines);
    return (has_ambient && has_camera && has_light);
}