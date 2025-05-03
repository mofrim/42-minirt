/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar_print_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:21:00 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/02 13:45:22 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Converts the floating point number INT_MIN <= d <= INT_MAX to a string.
 * Precision: 3 decimals.
 * WARNING: not suuper exact. F.ex. calling with 0.345 returns "0.344" :) */
// FIXME normify .. do we still need this in miniRT ?!?!?
char	*float_string(double d)
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
	return (fstr);
}

void	print_menu_text(t_mrt mrt, int x, int y, char *txt)
{
	mlx_string_put(mrt.mlx, mrt.win, x, y, rgb_to_int("00aa00"), txt);
}

void	print_mapinfo_float(t_mrt mrt, const char *txt, double prop, int *i)
{
	char	*prop_str;
	char	*msg;

	prop_str = float_string(prop);
	msg = ft_strjoin(txt, prop_str);
	print_menu_text(mrt, 15, 20 + (++(*i)) * 15, msg);
	free(msg);
	free(prop_str);
}

void	print_mapinfo(t_mrt mrt, const char *txt, int prop, int *i)
{
	char	*prop_str;
	char	*msg;

	prop_str = ft_itoa(prop);
	msg = ft_strjoin(txt, prop_str);
	print_menu_text(mrt, 15, 20 + (++(*i)) * 15, msg);
	free(msg);
	free(prop_str);
}
