/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:52:36 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/23 10:35:27 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Exit with error custom error msg, or not. */
void	error_exit(char *msg)
{
	ft_dprintf(STDERR_FILENO, "Error\nFatal: ");
	if (msg)
		perror(msg);
	else
		perror("Fatal Error");
	exit(EXIT_FAILURE);
}

/* Convenience error printing to stderr. Prints "Error\n" followed by the msg
 * given as argument. */
void	print_errmsg(char *msg, char *elem)
{
	if (!msg)
		return ;
	if (!elem)
		ft_dprintf(STDERR_FILENO, "Error\n-> %s\n", msg);
	if (elem)
		ft_dprintf(STDERR_FILENO, "Error\n-> %s: %s\n", msg, elem);
}

/* Convenience error printing to stderr. Prints "Error\n" followed by the msg
 * given as argument AND sets valid flag in tokenizer to false. */
void	printerr_set_invalid(char *msg, t_tokenizer *tok)
{
	if (!msg)
		return ;
	ft_dprintf(STDERR_FILENO, "Error\n-> %s\n", msg);
	tok->valid = false;
}

/* Print a errmsg to stderr, append a newline and exit with EXIT_FAILURE. */
void	exit_with_errmsg(char *msg)
{
	print_errmsg(msg, NULL);
	exit(EXIT_FAILURE);
}

/* Perform NULL check on pointer. error_exit with msg if NULL. */
void	nullcheck(void *p, char *msg)
{
	if (!p)
		error_exit(msg);
}
