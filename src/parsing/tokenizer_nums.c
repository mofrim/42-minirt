/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_nums.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/17 22:15:33 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	skip_sign(t_tokenizer *tok)
{
	if (tok->input[tok->pos] == '-' || tok->input[tok->pos] == '+')
		tok->pos++;
}

void	parse_digits(t_tokenizer *tok)
{
	while (ft_isdigit(tok->input[tok->pos]))
		tok->pos++;
}

void	parse_decimal(t_tokenizer *tok)
{
	if (tok->input[tok->pos] == '.')
	{
		tok->pos++;
		while (ft_isdigit(tok->input[tok->pos]))
			tok->pos++;
	}
}

t_token	*parse_number_token(t_tokenizer *tok)
{
	t_token	*token;
	int		start;
	char	*numstr;

	token = malloc(sizeof(t_token));
	nullcheck(token, "parse_number_token()");
	start = tok->pos;
	skip_sign(tok);
	parse_digits(tok);
	parse_decimal(tok);
	token->type = TOKEN_TYPE_NUMBER;
	numstr = ft_strndup(&tok->input[start], tok->pos - start);
	nullcheck(numstr, "parse_number_token()");
	token->u_value.num = ft_atof(numstr);
	free(numstr);
	debug_token(token, "in parse_number_token");
	return (token);
}

t_token	*parse_symbol_token(t_tokenizer *tokenizer)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	nullcheck(token, "parse_symbol_token()");
	token->type = TOKEN_TYPE_SYMBOL;
	token->u_value.str = ft_strndup(&tokenizer->input[tokenizer->pos], 1);
	tokenizer->pos++;
	return (token);
}
