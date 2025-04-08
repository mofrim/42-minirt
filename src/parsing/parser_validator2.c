/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:49:25 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/08 09:52:28 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static bool check_newline(t_tokenizer *tokenizer)
// {
// 	int	pos;

// 	pos = tokenizer->position;
// 	skip_whitespace(tokenizer);
// 	if (tokenizer->input[tokenizer->position] == '\n')
// 	{
// 		tokenizer->position++;
// 		return (true);
// 	}
// 	tokenizer->position = pos;
// 	return (false);
// }

// static bool is_keyword(char *str)
// {
//     return (ft_strcmp(str, "A") == 0 || 
//             ft_strcmp(str, "C") == 0 || 
//             ft_strcmp(str, "L") == 0 || 
//             ft_strcmp(str, "sp") == 0 || 
//             ft_strcmp(str, "pl") == 0 || 
//             ft_strcmp(str, "cy") == 0);
// }

// FIXME: refac && what happens if we do not have any token on a line? can this
// still happen at this stage?
void parse_tokens_recursive(t_parser *parser, t_scene *scene, bool *valid)
{
	t_token		*token;
	t_tokenizer	*line_tokenizer;
	t_parser	*line_parser;
	char		**lines;
	int			i;

	lines = ft_split(parser->tokenizer->input, '\n');
	nullcheck(lines, "parse_tokens_recursive()");
	i = -1;
	while (lines[++i] && *valid)
	{
		if (ft_strlen(lines[i]) == 0)
			continue;
		line_tokenizer = tokenizer_new(lines[i]);
		line_parser = parser_new(line_tokenizer);
		token = tokenizer_next(line_tokenizer);
		if (token && token->type == TOKEN_TYPE_KEYWORD)
		{
			handle_token_keyword(line_parser, scene, token);
			token_free(token);
			token = tokenizer_next(line_tokenizer);
			if (token)
			{
				ft_dprintf(STDERR_FILENO,
						"Error\nMultiple elements on one line");
				*valid = false;
				token_free(token);
			}
		}
		free(line_parser);
		tokenizer_free(line_tokenizer);
	}
	free_parts(lines);
}


