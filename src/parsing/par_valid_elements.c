/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_valid_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:30:00 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/04 11:49:35 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * Checks if the scene has the minimum required elements:
 * - Ambient Light (A)
 * - Camera (C)
 * - Light (L)
 */
bool has_minimum_required_elements(char *content)
{
	bool has_ambient = false;
	bool has_camera = false;
	bool has_light = false;
	char **lines;
	int i;
	
	if (!content)
		return (false);
	
	lines = ft_split(content, '\n');
	if (!lines)
		return (false);
	
	i = 0;
	while (lines[i])
	{
		// Skip empty lines and comments
		if (lines[i][0] == '\0' || lines[i][0] == '#')
		{
			i++;
			continue;
		}
		
		// Skip leading whitespace
		int j = 0;
		while (lines[i][j] && (lines[i][j] == ' ' || lines[i][j] == '\t'))
			j++;
		
		// Check for the element type
		if (lines[i][j] == 'A' && (lines[i][j+1] == ' ' || lines[i][j+1] == '\t'))
			has_ambient = true;
		else if (lines[i][j] == 'C' && (lines[i][j+1] == ' ' || lines[i][j+1] == '\t'))
			has_camera = true;
		else if (lines[i][j] == 'L' && (lines[i][j+1] == ' ' || lines[i][j+1] == '\t'))
			has_light = true;
		
		i++;
	}
	
	free_parts(lines);
	
	return (has_ambient && has_camera && has_light);
}
