/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_v3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:21:15 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/21 19:21:37 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
