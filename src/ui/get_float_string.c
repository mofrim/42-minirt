/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_float_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:42:46 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 09:42:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	convert3digits(char *fstr, double d, int i)
{
	fstr[i] = '.';
	d -= (int)d;
	d *= 10;
	fstr[++i] = (int)d + '0';
	d -= (int)d;
	d *= 10;
	fstr[++i] = (int)d + '0';
	d -= (int)d;
	d *= 10;
	fstr[++i] = (int)d + '0';
	fstr[++i] = 0;
}

/* Converts the floating point number INT_MIN <= d <= INT_MAX to a string.
 * Precision: 3 decimals.
 * WARNING: not suuper exact. F.ex. calling with 0.345 returns "0.344" :) */
char	*get_float_string(double d)
{
	char	*fstr;
	char	*itoa_str;
	int		i;

	fstr = malloc(16);
	i = 0;
	if (fabs(d) < 1 && d < 0)
	{
		fstr[0] = '-';
		i++;
	}
	itoa_str = ft_itoa((int)d);
	ft_strlcpy(&fstr[i], itoa_str, ft_strlen(itoa_str) + 1);
	i += ft_strlen(itoa_str);
	free(itoa_str);
	if (d < 0)
		d *= -1;
	convert3digits(fstr, d, i);
	return (fstr);
}
