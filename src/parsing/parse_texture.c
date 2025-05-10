/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:20:54 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/10 12:50:04 by fmaurer          ###   ########.fr       */
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
