/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/28 23:00:33 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_numeric(t_tokenizer *t);

t_tokenizer	*tokenizer_new(char *input)
{
	t_tokenizer	*tokenizer;

	tokenizer = malloc(sizeof(t_tokenizer));
	nullcheck(tokenizer, "tokenizer_new()");
	tokenizer->input = input;
	tokenizer->pos = 0;
	tokenizer->len = ft_strlen(input);
	tokenizer->valid = true;
	return (tokenizer);
}

t_token	*get_next_token(t_tokenizer *tok)
{
	skip_whitespace(tok);
	if (tok->input[tok->pos] == '\0' || tok->input[tok->pos] == '#')
		return (get_null_token());
	if (is_coordinate(tok))
		return (parse_coordinate(tok));
	else if (ft_isalpha(tok->input[tok->pos]))
		return (parse_keyword(tok));
	else if (is_numeric(tok))
		return (parse_number_token(tok));
	else
		return (NULL);
}

static int	is_numeric(t_tokenizer *t)
{
	return (ft_isdigit(t->input[t->pos]) || t->input[t->pos] == '-' || \
				t->input[t->pos] == '+' || t->input[t->pos] == '.');
}

void	skip_whitespace(t_tokenizer *t)
{
	while (t->input[t->pos] && ft_isspace(t->input[t->pos]))
		t->pos++;
}
