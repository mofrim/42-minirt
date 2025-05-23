/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:22:39 by jroseiro          #+#    #+#             */
/*   Updated: 2025/05/23 14:24:15 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Perform NULL check on pointer. error_exit with msg if NULL. */
void	nullcheck(void *p, char *msg)
{
	if (!p)
		error_exit(msg);
}

/* Free a pointer if != NULL. */
void	free_if_nonnull(void *p)
{
	if (p)
		free(p);
}
