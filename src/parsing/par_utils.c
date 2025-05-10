/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/05/10 10:23:31 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

/**
 * Get the next string from tokenizer input.
 *
 * Splits the tokenizer input by whitespaces starting from tok->pos. Then
 * returns the whole split.
 */
char	**get_tokstr_split(t_tokenizer *tok)
{
	char	**split;

	split = ft_whitesplit(&tok->input[tok->pos]);
	nullcheck(split, "check_parse_numtok()");
	return (split);
}

/* Free a token. Also set the param pointer to NULL to ensure pointer is not
 * reused or re-freed (at least make it checkable). */
void	token_free(t_token **tok)
{
	if (*tok)
	{
		if ((*tok)->type == TOKEN_TYPE_KEYWORD || (*tok)->type == TOKEN_TYPE_V3)
			free((*tok)->u_value.str);
		free(*tok);
		*tok = NULL;
	}
}

t_token	*get_null_token(void)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	nullcheck(tok, "get_null_token()");
	tok->type = TOKEN_TYPE_NULL;
	return (tok);
}
