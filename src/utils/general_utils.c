/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:22:39 by jroseiro          #+#    #+#             */
/*   Updated: 2025/05/26 10:42:10 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Perform NULL check on pointer. error_exit with msg if NULL. */
void	nullcheck(void *p, char *msg)
{
	if (!p)
		error_exit(msg);
}

/* Free a token if != NULL. */
void	free_tok_if_nonnull(void *p)
{
	t_token	*tok;

	tok = p;
	if (p)
	{
		if (tok->type == TOKEN_TYPE_KEYWORD)
			free(tok->u_value.str);
		free(p);
	}
}
