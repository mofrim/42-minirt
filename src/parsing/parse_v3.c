/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_v3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:47:53 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/23 10:24:06 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	parse_v3(t_tokenizer *tok)
{
	t_v3	v3;
	t_token	*token;
	char	**parts;

	v3 = (t_v3){0, 0, 0};
	token = get_next_token(tok);
	if (!token || token->type != TOKEN_TYPE_V3)
	{
		if (token)
			token_free(token);
		print_errmsg("expected vector format x,y,z", NULL);
		tok->valid = false;
		return (v3);
	}
	parts = ft_split(token->u_value.str, ',');
	if (!validate_vector(parts, &tok->valid))
	{
		ft_freesplit(&parts);
		token_free(token);
		return (v3);
	}
	v3 = (t_v3){ft_atof(parts[0]), ft_atof(parts[1]), ft_atof(parts[2])};
	ft_freesplit(&parts);
	token_free(token);
	return (v3);
}

bool	validate_vector(char **parts, bool *valid)
{
	int	i;

	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		print_errmsg("3d vector must have exactly 3 components", NULL);
		*valid = false;
		return (false);
	}
	i = -1;
	while (++i < 3)
	{
		if (!ft_is_snumstr(parts[i]))
		{
			print_errmsg("vector components must be numeric", NULL);
			*valid = false;
			return (false);
		}
	}
	return (true);
}
