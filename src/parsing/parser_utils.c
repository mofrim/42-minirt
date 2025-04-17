/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/17 09:38:01 by fmaurer          ###   ########.fr       */
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

// QUESTION: maybe just use an assignment like `v = (t_v3){0, 0, 0};`. IMHO
// there is no need for an extra function here.
t_v3	parse_default_v3(void)
{
	t_v3	v3;

	v3.x = 0;
	v3.y = 0;
	v3.z = 0;
	return (v3);
}

t_v3	parse_v3_from_parts(char **parts)
{
	t_v3	v3;

	v3.x = ft_atof(parts[0]);
	v3.y = ft_atof(parts[1]);
	v3.z = ft_atof(parts[2]);
	return (v3);
}

t_v3 parse_v3(t_tokenizer *tokenizer, bool *valid)
{
    t_v3	v3;
    t_token	*token;
    char	**parts;

    v3 = parse_default_v3();
    token = tokenizer_next(tokenizer);
    if (!token || token->type != TOKEN_TYPE_V3)
    {
        if (token)
            token_free(token);
        ft_putendl_fd("Error: Expected vector format x,y,z", 2);
        *valid = false;
        return (v3);
    }
    parts = ft_split(token->u_value.str, ',');
    if (!validate_vector_components(parts, valid))
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
