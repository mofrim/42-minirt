/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_parse_coord_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:19:02 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/23 09:49:51 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_token	*parse_coordinate(t_tokenizer *tok)
{
	t_token	*token;
	int		start;

	token = malloc(sizeof(t_token));
	nullcheck(token, "parse_coordinate()");
	start = tok->pos;
	while (tok->input[tok->pos] && !ft_isspace(tok->input[tok->pos]))
		tok->pos++;
	token->type = TOKEN_TYPE_V3;
	token->u_value.str = ft_strndup(&tok->input[start], tok->pos - start);
	debug_token(token, "in parse_coordinate");
	return (token);
}

int	is_coordinate(t_tokenizer *tok)
{
	size_t	i;
	int		comma_count;

	i = 0;
	comma_count = 0;
	if (!(ft_isdigit(tok->input[tok->pos]) || tok->input[tok->pos] == '-' || \
				tok->input[tok->pos] == '+'))
		return (0);
	while ((tok->pos + i) < tok->len && !ft_isspace(tok->input[tok->pos + i]))
	{
		if (tok->input[tok->pos + i] == ',')
			comma_count++;
		else if (!ft_isdigit(tok->input[tok->pos + i]) && \
				tok->input[tok->pos + i] != '.' && \
				tok->input[tok->pos + i] != '-' && \
				tok->input[tok->pos + i] != '+')
			return (0);
		i++;
	}
	return (comma_count == 2);
}

t_token	*parse_keyword(t_tokenizer *tok)
{
	t_token	*token;
	int		start;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	start = tok->pos;
	if (ft_isalpha(tok->input[tok->pos + 1]))
		tok->pos += 2;
	else
		tok->pos++;
	token->type = TOKEN_TYPE_KEYWORD;
	token->u_value.str = ft_strndup(&tok->input[start], tok->pos - start);
	debug_token(token, "in parse_keyword");
	return (token);
}
