/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_validate_colr_vector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:56:45 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/18 22:12:53 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool validate_color(char **parts, bool *valid)
{
	int r, g, b;

	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		print_errmsg("color must have exactly 3 components");
		*valid = false;
		return (false);
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; parts[i][j]; j++)
		{
			if (!ft_isdigit(parts[i][j]))
			{
				print_errmsg("color components must be numeric");
				*valid = false;
				return (false);
			}
		}
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		print_errmsg("color components must be between 0 and 255");
		*valid = false;
		return (false);
	}
	return (true);
}

static bool	set_invalid_print_err(char *msg, bool *valid)
{
		print_errmsg(msg);
		*valid = false;
		return (false);
}

bool	validate_vector(char **parts, bool *valid)
{
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
		return(set_invalid_print_err("Vector must have exactly 3 components",
					valid));
	for (int i = 0; i < 3; i++)
	{
		int j = 0;
		if (parts[i][j] == '-' || parts[i][j] == '+')
			j++;
		if (!ft_isdigit(parts[i][j]))
			return(set_invalid_print_err("Vector components must be numeric",
						valid));
		while (ft_isdigit(parts[i][j]))
			j++;
		if (parts[i][j] == '.')
		{
			j++;
			if (!ft_isdigit(parts[i][j]))
				return(set_invalid_print_err("Invalid floating point format",
							valid));
			while (ft_isdigit(parts[i][j]))
				j++;
		}
		if (parts[i][j] != '\0')
			return(set_invalid_print_err("Invalid character in vector component",
						valid));
	}
	return (true);
}
