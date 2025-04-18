/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:52:15 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/19 01:06:21 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// FIXME add validation check here?!
// rewrite to have the same structure as parse_color or the like!
double	parse_number(t_tokenizer *tokenizer)
{
	t_token	*token;
	double	value;

	skip_whitespace(tokenizer);
	token = parse_number_token(tokenizer);
	if (!token)
		return (0.0);
	value = token->u_value.num;
	token_free(token);
	return (value);
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
