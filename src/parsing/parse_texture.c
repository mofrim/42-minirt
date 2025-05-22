/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:20:54 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/22 14:37:17 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	**get_tokstr_split(t_tokenizer *tok);

char	*parse_texture_maybe(t_tokenizer *tok)
{
	char	**toksplit;
	char	*tex_fname;

	toksplit = get_tokstr_split(tok);
	if (toksplit && toksplit[0] && !ft_strcmp("tex", toksplit[0]) && \
toksplit[1])
	{
		tex_fname = ft_strdup(toksplit[1]);
		skip_whitespace(tok);
		tok->pos += ft_strlen(toksplit[0]);
		skip_whitespace(tok);
		tok->pos += ft_strlen(toksplit[1]);
		ft_freesplit(&toksplit);
		return (tex_fname);
	}
	if (toksplit)
		ft_freesplit(&toksplit);
	return (NULL);
}

char	*parse_nmap_maybe(t_tokenizer *tok)
{
	char	**toksplit;
	char	*tex_fname;

	toksplit = get_tokstr_split(tok);
	if (toksplit && toksplit[0] && !ft_strcmp("nmap", toksplit[0]) && \
toksplit[1])
	{
		tex_fname = ft_strdup(toksplit[1]);
		skip_whitespace(tok);
		tok->pos += ft_strlen(toksplit[0]);
		skip_whitespace(tok);
		tok->pos += ft_strlen(toksplit[1]);
		ft_freesplit(&toksplit);
		return (tex_fname);
	}
	if (toksplit)
		ft_freesplit(&toksplit);
	return (NULL);
}

/* Only parse "bump" if followed by the "bumpiness" float number and "tex". */
bool	parse_bump_maybe(t_tokenizer *tok)
{
	char	**toksplit;

	toksplit = get_tokstr_split(tok);
	if (toksplit && toksplit[0] && !ft_strcmp("bump", toksplit[0]) && \
toksplit[1] && ft_is_unumstr(toksplit[1]) && toksplit[2] && \
!ft_strcmp("tex", toksplit[2]))
	{
		skip_whitespace(tok);
		tok->pos += ft_strlen(toksplit[0]);
		ft_freesplit(&toksplit);
		return (true);
	}
	if (toksplit)
		ft_freesplit(&toksplit);
	return (false);
}

/* Only parse "checker" if followed by the "checker_scale" float number and
 * "tex". */
bool	parse_checker_maybe(t_tokenizer *tok)
{
	char	**toksplit;

	toksplit = get_tokstr_split(tok);
	if (toksplit && toksplit[0] && !ft_strcmp("checker", toksplit[0]) && \
toksplit[1] && ft_is_unumstr(toksplit[1]))
	{
		skip_whitespace(tok);
		tok->pos += ft_strlen(toksplit[0]);
		ft_freesplit(&toksplit);
		return (true);
	}
	if (toksplit)
		ft_freesplit(&toksplit);
	return (false);
}

/* Only parse hypercheker if followed by the "checker_scale" float number and
 * "tex". */
int	parse_hyperchecker_maybe(t_tokenizer *tok)
{
	char	**toksplit;

	toksplit = get_tokstr_split(tok);
	if (toksplit && toksplit[0] && (!ft_strcmp("checker", toksplit[0]) || \
!ft_strcmp("stripechecker", toksplit[0]) || \
!ft_strcmp("spacechecker", toksplit[0])) && \
toksplit[1] && ft_is_unumstr(toksplit[1]))
	{
		skip_whitespace(tok);
		tok->pos += ft_strlen(toksplit[0]);
		if (!ft_strcmp("checker", toksplit[0]))
			return (ft_freesplit(&toksplit), 1);
		if (!ft_strcmp("stripechecker", toksplit[0]))
			return (ft_freesplit(&toksplit), 2);
		if (!ft_strcmp("spacechecker", toksplit[0]))
			return (ft_freesplit(&toksplit), 3);
	}
	if (toksplit)
		ft_freesplit(&toksplit);
	return (0);
}
