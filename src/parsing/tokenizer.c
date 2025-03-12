/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/12 17:28:40 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Create a new tokenizer
t_tokenizer *tokenizer_new(char *input)
{
    t_tokenizer *tokenizer = malloc(sizeof(t_tokenizer));
    if (!tokenizer)
        return NULL;
    tokenizer->input = input;
    tokenizer->position = 0;
    return tokenizer;
}

// Get the next token from the tokenizer
t_token *tokenizer_next(t_tokenizer *tokenizer)
{
    // Skip whitespace
    while (ft_isspace(tokenizer->input[tokenizer->position]))
        tokenizer->position++;
    // Check for end of input
    if (tokenizer->input[tokenizer->position] == '\0')
        return NULL;
    // Create a new token
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    // Check for keyword
    if (ft_isalpha(tokenizer->input[tokenizer->position]))
    {
        token->type = TOKEN_TYPE_KEYWORD;
        token->u_value.str = parse_keyword(tokenizer);
    }
    // Check for identifier
    else if (ft_isalpha(tokenizer->input[tokenizer->position]))
    {
        token->type = TOKEN_TYPE_IDENTIFIER;
        token->u_value.str = parse_identifier(tokenizer);
    }
    // Check for number
    else if (ft_isdigit(tokenizer->input[tokenizer->position]))
    {
        token->type = TOKEN_TYPE_NUMBER;
        token->u_value.num = parse_number(tokenizer);
    }
    // Check for symbol
    else
    {
        token->type = TOKEN_TYPE_SYMBOL;
        token->u_value.str = parse_symbol(tokenizer);
    }
    return token;
}

// Free the tokenizer
void tokenizer_free(t_tokenizer *tokenizer)
{
    free(tokenizer);
}

// Parse a keyword
char *parse_keyword(t_tokenizer *tokenizer)
{
    int start;
    start = tokenizer->position;
    while (ft_isalpha(tokenizer->input[tokenizer->position]))
        tokenizer->position++;
    return (ft_strndup(&tokenizer->input[start], tokenizer->position - start));
}

// Parse an identifier
char *parse_identifier(t_tokenizer *tokenizer)
{
    int start = tokenizer->position;
    while (ft_isalnum(tokenizer->input[tokenizer->position]))
        tokenizer->position++;
    return (ft_strndup(&tokenizer->input[start], tokenizer->position - start));
}

// Parse a number (needs refactoring, just for testing)
double parse_number(t_tokenizer *tokenizer)
{
    int start;
    int end;
    char *num_str;

    start = tokenizer->position;
    end = start;
    // Handle potential leading signs (+ or -)
    if (tokenizer->input[end] == '+' || tokenizer->input[end] == '-')
        end++;

    // Parse digits before the decimal point
    while (ft_isdigit(tokenizer->input[end]))
        end++;

    // Parse decimal point and digits after it
    if (tokenizer->input[end] == '.')
    {
        end++;
        while (ft_isdigit(tokenizer->input[end]))
        {
            end++;
        }
    }

    // Extract the number string
    num_str = ft_strndup(&tokenizer->input[start], end - start);
    if (!num_str)
    {
        // Handle allocation error (return a default value or error)
        return (0.0); // Or handle the error as appropriate
    }

    // Convert the string to a double
    double num_value = atof(num_str);

    // Free the allocated string
    free(num_str);

    // Update tokenizer position
    tokenizer->position = end;

    return (num_value);
}

// Parse a symbol
char *parse_symbol(t_tokenizer *tokenizer)
{
    char *symbol = malloc(sizeof(char) * 2);
    if (!symbol)
        return NULL;
    symbol[0] = tokenizer->input[tokenizer->position++];
    symbol[1] = '\0';
    return (symbol);
}

