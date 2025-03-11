/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/11 19:07:16 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
    while (isspace(tokenizer->input[tokenizer->position]))
        tokenizer->position++;
    // Check for end of input
    if (tokenizer->input[tokenizer->position] == '\0')
        return NULL;
    // Create a new token
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    // Check for keyword
    if (isalpha(tokenizer->input[tokenizer->position]))
    {
        token->type = TOKEN_TYPE_KEYWORD;
        token->value = parse_keyword(tokenizer);
    }
    // Check for identifier
    else if (isalpha(tokenizer->input[tokenizer->position]))
    {
        token->type = TOKEN_TYPE_IDENTIFIER;
        token->value = parse_identifier(tokenizer);
    }
    // Check for number
    else if (isdigit(tokenizer->input[tokenizer->position]))
    {
        token->type = TOKEN_TYPE_NUMBER;
        token->value = parse_number(tokenizer);
    }
    // Check for symbol
    else
    {
        token->type = TOKEN_TYPE_SYMBOL;
        token->value = parse_symbol(tokenizer);
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
    int start = tokenizer->position;
    while (isalpha(tokenizer->input[tokenizer->position]))
        tokenizer->position++;
    return strndup(&tokenizer->input[start], tokenizer->position - start);
}

// Parse an identifier
char *parse_identifier(t_tokenizer *tokenizer)
{
    int start = tokenizer->position;
    while (isalnum(tokenizer->input[tokenizer->position]))
        tokenizer->position++;
    return strndup(&tokenizer->input[start], tokenizer->position - start);
}

// Parse a number
char *parse_number(t_tokenizer *tokenizer)
{
    int start = tokenizer->position;
    while (isdigit(tokenizer->input[tokenizer->position]))
        tokenizer->position++;
    return strndup(&tokenizer->input[start], tokenizer->position - start);
}

// Parse a symbol
char *parse_symbol(t_tokenizer *tokenizer)
{
    char *symbol = malloc(sizeof(char) * 2);
    if (!symbol)
        return NULL;
    symbol[0] = tokenizer->input[tokenizer->position++];
    symbol[1] = '\0';
    return symbol;
}