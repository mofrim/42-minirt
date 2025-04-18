/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_lineparse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:05:30 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/19 01:39:47 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	parse_line(char *line, t_scene *scene);

/**
 * Parse the scenefile line by line.
 *
 * Returns -1 if parsing failed somewhere down the line.
 */
// QUESTION: Can it happen that there is no token on a line? Or is this already
// ruled out before?
int	lineparse_scenefile(t_tokenizer *tokenizer, t_scene *scene)
{
	bool		valid;
	char		**lines;
	int			i;

	valid = true;
	lines = ft_split(tokenizer->input, '\n');
	nullcheck(lines, "lineparse_scenefile()");
	i = -1;
	while (lines[++i] && valid)
	{
		if (ft_strlen(lines[i]) == 0)
			continue;
		valid = parse_line(lines[i], scene);
	}
	free_parts(lines);
	if (!valid)
		return (-1);
	return (0);
}

/* Extracted routine for parsing one line from the scenefile. */
bool	parse_line(char *line, t_scene *scene)
{
	t_token		*token;
	t_tokenizer	*line_tokenizer;
	bool		valid;

	valid = true;
	line_tokenizer = tokenizer_new(line);
	token = get_next_token(line_tokenizer);
	if (token && token->type == TOKEN_TYPE_KEYWORD)
	{
		handle_token_keyword(scene, line_tokenizer, token->u_value.str);
		token_free(token);
		token = get_next_token(line_tokenizer);
		if (token)
		{
			token_free(token);
			print_errmsg("malformed line in scenefile.");
			valid = false;
		}
	}
	free(line_tokenizer);
	return (valid);
}
