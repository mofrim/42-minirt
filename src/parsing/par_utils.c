/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/19 01:02:42 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_parts_helper(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

t_v3	parse_v3_from_parts(char **parts)
{
	t_v3	v3;

	v3.x = ft_atof(parts[0]);
	v3.y = ft_atof(parts[1]);
	v3.z = ft_atof(parts[2]);
	return (v3);
}

t_v3	parse_v3(t_tokenizer *tokenizer, bool *valid)
{
	t_v3	v3;
	t_token	*token;
	char	**parts;

	v3 = (t_v3){0, 0, 0};
	token = get_next_token(tokenizer);
	if (!token || token->type != TOKEN_TYPE_V3)
	{
		if (token)
			token_free(token);
		print_errmsg("expected vector format x,y,z");
		*valid = false;
		return (v3);
	}
	parts = ft_split(token->u_value.str, ',');
	if (!validate_vector(parts, valid))
	{
		free_parts(parts);
		token_free(token);
		return (v3);
	}
	v3 = parse_v3_from_parts(parts);
	free_parts(parts);
	token_free(token);
	return (v3);
}

void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}
