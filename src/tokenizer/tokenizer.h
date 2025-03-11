/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:35:39 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/11 19:01:35 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "src/include/minirt.h"

// Define the different types of tokens
typedef enum e_tokentype {
	TOKEN_TYPE_KEYWORD,
	TOKEN_TYPE_IDENTIFIER,
	TOKEN_TYPE_NUMBER,
	TOKEN_TYPE_SYMBOL,
} t_tokentype;

// Define the structure of a token
typedef struct s_token {
	t_tokentype type;
	char *value;
} t_token;

// Define the tokenizer
typedef struct s_tokenizer {
	char *input;
	int position;
} t_tokenizer;

// Create a new tokenizer
t_tokenizer *tokenizer_new(char *input);

// Get the next token from the tokenizer
t_token *tokenizer_next(t_tokenizer *tokenizer);

// Free the tokenizer
void tokenizer_free(t_tokenizer *tokenizer);

#endif