/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:49:25 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/04 00:08:46 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool check_newline(t_tokenizer *tokenizer)
{
	int	pos;

	pos = tokenizer->position;
	skip_whitespace(tokenizer);
	if (tokenizer->input[tokenizer->position] == '\n')
	{
		tokenizer->position++;
		return (true);
	}
	tokenizer->position = pos;
	return (false);
}

static bool is_keyword(char *str)
{
    return (ft_strcmp(str, "A") == 0 || 
            ft_strcmp(str, "C") == 0 || 
            ft_strcmp(str, "L") == 0 || 
            ft_strcmp(str, "sp") == 0 || 
            ft_strcmp(str, "pl") == 0 || 
            ft_strcmp(str, "cy") == 0);
}

void parse_tokens_recursive(t_parser *parser, t_scene *scene, bool *valid)
{
    t_token *token;
    char **lines;
    int i;
    
    // Split input by newlines
    lines = ft_split(parser->tokenizer->input, '\n');
    if (!lines)
        return;
    
    i = 0;
    while (lines[i] && *valid)
    {
        // Skip empty lines
        if (ft_strlen(lines[i]) == 0)
        {
            i++;
            continue;
        }
        
        // Create a temporary tokenizer for this line
        t_tokenizer *line_tokenizer = tokenizer_new(lines[i]);
        t_parser *line_parser = parser_new(line_tokenizer);
        
        // Parse the single line
        token = tokenizer_next(line_tokenizer);
        if (token && token->type == TOKEN_TYPE_KEYWORD)
        {
            handle_token_keyword(line_parser, scene, token);
            token_free(token);
            
            // Check if there are more tokens on this line (should be none)
            token = tokenizer_next(line_tokenizer);
            if (token)
            {
                ft_putendl_fd("Error: Multiple elements on one line", 2);
                *valid = false;
                token_free(token);
            }
        }
        
        // Clean up
        parser_free(line_parser);
        tokenizer_free(line_tokenizer);
        i++;
    }
    
    // Free the split lines
    free_parts(lines);
}


