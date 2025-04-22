/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/22 22:34:58 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_token	*parse_number_token(t_tokenizer *tok)
{
	t_token	*token;
	char	*numstr;

	numstr = get_tokstr(tok);
	if (!ft_is_unumstr(numstr))
	{
		tok->valid = false;
		tok->pos += ft_strlen(numstr);
		return (print_errmsg("unsigned float value expected"), NULL);
	}
	token = malloc(sizeof(t_token));
	nullcheck(token, "parse_number_token()");
	token->type = TOKEN_TYPE_NUM;
	token->u_value.num = ft_atof(numstr);
	tok->pos += ft_strlen(numstr);
	debug_token(token, "in parse_number_token");
	free(numstr);
	return (token);
}

/* Parse an unsigned positive float number. Parsing only needs float-precision,
 * in the calculations we want double, but this will be automatically casted in
 * assignments. */
float	parse_pos_num(t_tokenizer *tok)
{
	t_token	*token;
	float	value;

	skip_whitespace(tok);
	token = parse_number_token(tok);
	if (!token)
		return (0.0);
	value = token->u_value.num;
	token_free(token);
	return (value);
}
