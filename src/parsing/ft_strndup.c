/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:42:54 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/14 15:42:16 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	len;
	size_t i;
	char *dup;

	len = 0;
	i = 0;
	while (len < n && src[len] != '\0')
		len++;

	dup = (char *)malloc(len + 1);

	if (dup == NULL)
		return NULL;

	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[len] = '\0';

	return (dup);
}
