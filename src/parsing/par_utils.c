/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/22 20:52:21 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	parse_v3_from_parts(char **parts)
{
	t_v3	v3;

	v3.x = ft_atof(parts[0]);
	v3.y = ft_atof(parts[1]);
	v3.z = ft_atof(parts[2]);
	return (v3);
}

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
		print_errmsg("expected vector format x,y,z");
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
	v3 = parse_v3_from_parts(parts);
	ft_freesplit(&parts);
	token_free(token);
	return (v3);
}

/**
 * Get the next string from tokenizer input.
 *
 * Splits the tokenizer input by whitespaces starting from tok->pos. Then
 * returns the first split elem.
 */
char	*get_tokstr(t_tokenizer *tok)
{
	char	**split;
	char	*tokstr;

	split = ft_whitesplit(&tok->input[tok->pos]);
	nullcheck(split, "check_parse_numtok()");
	tokstr = NULL;
	if (split[0])
		tokstr = ft_strdup(split[0]);
	ft_freesplit(&split);
	return (tokstr);
}

/* Free a token. */
void	token_free(t_token *tok)
{
	if (tok)
	{
		if (tok->type == TOKEN_TYPE_KEYWORD || tok->type == TOKEN_TYPE_V3)
			free(tok->u_value.str);
		free(tok);
	}
}
