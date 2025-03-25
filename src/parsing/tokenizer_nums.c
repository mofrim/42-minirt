/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_nums.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/28 15:35:10 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	skip_sign(t_tokenizer *tokenizer)
{
	if (tokenizer->input[tokenizer->position] == '-' || \
		tokenizer->input[tokenizer->position] == '+')
		tokenizer->position++;
}

void	parse_digits(t_tokenizer *tokenizer)
{
	while (ft_isdigit(tokenizer->input[tokenizer->position]))
		tokenizer->position++;
}

void	parse_decimal(t_tokenizer *tokenizer)
{
	if (tokenizer->input[tokenizer->position] == '.')
	{
		tokenizer->position++;
		while (ft_isdigit(tokenizer->input[tokenizer->position]))
			tokenizer->position++;
	}
}

t_token	*parse_number_token(t_tokenizer *tokenizer)
{
	t_token	*token;
	int		start;
	char	*numstr;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	start = tokenizer->position;
	skip_sign(tokenizer);
	parse_digits(tokenizer);
	parse_decimal(tokenizer);
	token->type = TOKEN_TYPE_NUMBER;
	numstr = ft_strndup(&tokenizer->input[start], tokenizer->position - start);
	token->u_value.num = ft_atof(numstr);
	free(numstr);
	debug_token(token, "in parse_number_token");
	return (token);
}

t_token	*parse_symbol_token(t_tokenizer *tokenizer)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_TYPE_SYMBOL;
	token->u_value.str = ft_strndup(&tokenizer->input[tokenizer->position], 1);
	tokenizer->position++;
	return (token);
}
