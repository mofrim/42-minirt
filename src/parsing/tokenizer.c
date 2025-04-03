/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/03 13:19:00 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tokenizer	*tokenizer_new(char *input)
{
	t_tokenizer	*tokenizer;

	tokenizer = malloc(sizeof(t_tokenizer));
	if (!tokenizer)
		return (NULL);
	tokenizer->input = input;
	tokenizer->position = 0;
	tokenizer->len = ft_strlen(input);
	return (tokenizer);
}

void	tokenizer_free(t_tokenizer *tokenizer)
{
	free(tokenizer);
}

void	skip_whitespace(t_tokenizer *tokenizer)
{
	while (tokenizer->input[tokenizer->position] && \
			(tokenizer->input[tokenizer->position] == ' ' || \
			tokenizer->input[tokenizer->position] == '\t'))
		tokenizer->position++;
}

t_token	*parse_coordinate(t_tokenizer *tokenizer)
{
	t_token	*token;
	int		start;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	start = tokenizer->position;
	while (tokenizer->input[tokenizer->position] && \
			tokenizer->input[tokenizer->position] != ' ' && \
			tokenizer->input[tokenizer->position] != '\t' && \
			tokenizer->input[tokenizer->position] != '\n')
		tokenizer->position++;
	token->type = TOKEN_TYPE_V3;
	token->u_value.str = ft_strndup(&tokenizer->input[start], \
								tokenizer->position - start);
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
	start = tokenizer->position;
	if (ft_isalpha(tokenizer->input[tokenizer->position + 1]))
		tokenizer->position += 2;
	else
		tokenizer->position++;
	token->type = TOKEN_TYPE_KEYWORD;
	token->u_value.str = ft_strndup(&tokenizer->input[start], \
								tokenizer->position - start);
	return (token);
}
