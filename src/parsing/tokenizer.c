/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/17 14:18:16 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tokenizer	*tokenizer_new(char *input)
{
	t_tokenizer	*tokenizer;

	tokenizer = malloc(sizeof(t_tokenizer));
	nullcheck(tokenizer, "tokenizer_new()");
	tokenizer->input = input;
	tokenizer->pos = 0;
	tokenizer->len = ft_strlen(input);
	return (tokenizer);
}

void	skip_whitespace(t_tokenizer *t)
{
	while (t->input[t->pos] && \
			(t->input[t->pos] == ' ' || \
			t->input[t->pos] == '\t' || \
			t->input[t->pos] == '\n'))
		t->pos++;
}

t_token	*parse_coordinate(t_tokenizer *tokenizer)
{
	t_token	*token;
	int		start;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	start = tokenizer->pos;
	while (tokenizer->input[tokenizer->pos] && \
			tokenizer->input[tokenizer->pos] != ' ' && \
			tokenizer->input[tokenizer->pos] != '\t' && \
			tokenizer->input[tokenizer->pos] != '\n')
		tokenizer->pos++;
	token->type = TOKEN_TYPE_V3;
	token->u_value.str = ft_strndup(&tokenizer->input[start], \
								tokenizer->pos - start);
	debug_token(token, "in parse_coordinate");
	return (token);
}

t_token	*parse_identifier(t_tokenizer *tokenizer)
{
	t_token	*token;
	int		start;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	start = tokenizer->pos;
	if (ft_isalpha(tokenizer->input[tokenizer->pos + 1]))
		tokenizer->pos += 2;
	else
		tokenizer->pos++;
	token->type = TOKEN_TYPE_KEYWORD;
	token->u_value.str = ft_strndup(&tokenizer->input[start], \
								tokenizer->pos - start);
	debug_token(token, "in parse_identifier");
	return (token);
}
