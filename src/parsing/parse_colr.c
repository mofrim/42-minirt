/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:56:45 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/29 10:44:46 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Parse a color. Also validates if the 3-tuple found is really a valid color.
 * If not -> errmsg is printed and tok->valid is set to false. */
t_colr	parse_color(t_tokenizer *tok)
{
	t_colr	colr;
	t_token	*token;
	char	**parts;

	colr = (t_colr){0, 0, 0, 0};
	token = get_next_token(tok);
	if (!token || (token && token->type != TOKEN_TYPE_V3))
	{
		if (token)
			token_free(&token);
		printerr_set_invalid("expected color format r,g,b", &tok->valid);
		return (colr);
	}
	parts = ft_split(token->u_value.str, ',');
	if (!validate_color(parts, &tok->valid))
	{
		ft_freesplit(&parts);
		token_free(&token);
		return (colr);
	}
	colr = (t_colr){ft_atoi(parts[0]), ft_atoi(parts[1]), ft_atoi(parts[2]), 0};
	ft_freesplit(&parts);
	token_free(&token);
	return (colr);
}

static int	is_valid_colrcomp(char *comp)
{
	int	c;

	if (!ft_is_uinumstr(comp))
		return (false);
	c = ft_atoi(comp);
	if (c < 0 || 255 < c)
		return (false);
	return (true);
}

bool	validate_color(char **parts, bool *valid)
{
	int	i;

	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		*valid = false;
		print_errmsg("color must have exactly 3 components", NULL);
		return (false);
	}
	i = -1;
	while (parts[++i])
	{
		if (!is_valid_colrcomp(parts[i]))
		{
			*valid = false;
			print_errmsg("invalid color component", parts[i]);
			return (false);
		}
	}
	return (true);
}
