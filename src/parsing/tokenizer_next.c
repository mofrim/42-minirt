/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/17 14:18:16 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// In tokenizer_next.c, improve is_coordinate function
int is_coordinate(t_tokenizer *tokenizer)
{
    int i;
    int comma_count;
	
	i = 0;
	comma_count = 0;
    // Check if it starts with a digit or sign
    if (!(ft_isdigit(tokenizer->input[tokenizer->pos]) || 
          tokenizer->input[tokenizer->pos] == '-' || 
          tokenizer->input[tokenizer->pos] == '+'))
        return (0);
    // Count commas and ensure all characters are valid for coordinates
    while ((size_t)(tokenizer->pos + i) < tokenizer->len && 
           !ft_isspace(tokenizer->input[tokenizer->pos + i]))
    {
        if (tokenizer->input[tokenizer->pos + i] == ',')
            comma_count++;
        else if (!ft_isdigit(tokenizer->input[tokenizer->pos + i]) && 
                 tokenizer->input[tokenizer->pos + i] != '.' && 
                 tokenizer->input[tokenizer->pos + i] != '-' && 
                 tokenizer->input[tokenizer->pos + i] != '+')
            return (0); // Invalid character for coordinate
        i++;
    }
    // A valid coordinate has exactly 2 commas (x,y,z)
    return (comma_count == 2);
}

int	is_identifier(t_tokenizer *tokenizer)
{
	return (ft_isalpha(tokenizer->input[tokenizer->pos]));
}

int	is_numeric(t_tokenizer *tokenizer)
{
	return (ft_isdigit(tokenizer->input[tokenizer->pos]) || \
				tokenizer->input[tokenizer->pos] == '-' || \
				tokenizer->input[tokenizer->pos] == '+' || \
			tokenizer->input[tokenizer->pos] == '.');
}

t_token	*tokenizer_next(t_tokenizer *tokenizer)
{
	skip_whitespace(tokenizer);
	if (tokenizer->input[tokenizer->pos] == '\0')
		return (NULL);
	if (is_coordinate(tokenizer))
		return (parse_coordinate(tokenizer));
	else if (is_identifier(tokenizer))
		return (parse_identifier(tokenizer));
	else if (is_numeric(tokenizer))
		return (parse_number_token(tokenizer));
	else
		return (parse_symbol_token(tokenizer));
}

char	*parse_keyword(t_tokenizer *tokenizer)
{
	int	start;

	start = tokenizer->pos;
	while (ft_isalpha(tokenizer->input[tokenizer->pos]))
		tokenizer->pos++;
	return (ft_strndup(&tokenizer->input[start], tokenizer->pos - start));
}
