/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/05/06 20:45:03 by fmaurer          ###   ########.fr       */
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
		return (print_errmsg("unsigned float value expected", numstr), NULL);
	}
	token = malloc(sizeof(t_token));
	nullcheck(token, "parse_number_token()");
	token->type = TOKEN_TYPE_NUM;
	token->u_value.num = ft_atof(numstr);
	tok->pos += ft_strlen(numstr);
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
		return (-1.0);
	value = token->u_value.num;
	token_free(&token);
	return (value);
}

/**
 * Maybe parse a positive float.
 *
 * This is used for parsing possible specular refelection values as the last
 * token of an object defining line. If there is something after the colr of an
 * obj but it is not a positive number this has to be a syntax error. this is
 * why we do not advance the tok->pos in this case. By doing so the something
 * will be detected as an error in `parse_line`, but we don't have to deal with
 * it at all in here.
 *
 * Returns -1 if nothing valid is found. The float value otherwise.
 */
float parse_pos_num_maybe(t_tokenizer *tok)
{
	float	value;
	char	*numstr;

	skip_whitespace(tok);
	numstr = get_tokstr(tok);
	if (!ft_is_unumstr(numstr))
		return (-1.0);
	value = ft_atof(numstr);
	tok->pos += ft_strlen(numstr);
	free(numstr);
	return (value);
}
