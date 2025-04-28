/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_lineparse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:05:30 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/28 23:03:45 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	parse_line(char *line, t_scene *scene);

/**
 * Parse the scenefile line by line.
 *
 * Returns -1 if parsing failed somewhere down the line.
 */
int	lineparse_scenefile(char *file_content, t_scene *scene)
{
	bool	valid;
	char	**lines;
	int		i;

	valid = true;
	lines = ft_split(file_content, '\n');
	nullcheck(lines, "lineparse_scenefile()");
	i = -1;
	while (lines[++i] && valid)
	{
		if (ft_strlen(lines[i]) == 0)
			continue ;
		valid = parse_line(lines[i], scene);
	}
	ft_freesplit(&lines);
	if (!valid)
		return (-1);
	return (0);
}

/* Extracted routine for parsing one line from the scenefile. */
bool	parse_line(char *line, t_scene *scene)
{
	t_token		*token;
	t_tokenizer	*line_tok;

	line_tok = tokenizer_new(line);
	token = get_next_token(line_tok);
	if (token && token->type == TOKEN_TYPE_KEYWORD)
	{
		handle_token_keyword(scene, line_tok, token->u_value.str);
		token_free(&token);
		if (line_tok->valid)
		{
			token = get_next_token(line_tok);
			if (token && token->type != TOKEN_TYPE_NULL)
				printerr_set_invalid("malformed line in scenefile",
					&line_tok->valid);
		}
	}
	if (token)
		token_free(&token);
	else
		printerr_set_invalid("malformed line in scenefile", &line_tok->valid);
	if (line_tok->valid)
		return (free(line_tok), true);
	return (free(line_tok), false);
}
