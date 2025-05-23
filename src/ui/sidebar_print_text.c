/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar_print_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:21:00 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 18:16:31 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_float_string(double d);

/* Wrapper around mlx_string_put for applying our color. */
void	print_menu_text(t_mrt mrt, int x, int y, char *txt)
{
	mlx_string_put(mrt.mlx, mrt.win, x, y, mrt.side_thm.txt_colr, txt);
}

/* Print a menu header line. */
void	print_menu_header(t_mrt mrt, int x, int y, char *txt)
{
	mlx_string_put(mrt.mlx, mrt.win, x, y, mrt.side_thm.head_colr, txt);
}

void	print_mapinfo_float(t_mrt mrt, const char *txt, double prop, int *i)
{
	char	*prop_str;
	char	*msg;

	prop_str = get_float_string(prop);
	msg = ft_strjoin(txt, prop_str);
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, msg);
	free(msg);
	free(prop_str);
}

void	print_mapinfo(t_mrt mrt, const char *txt, int prop, int *i)
{
	char	*prop_str;
	char	*msg;

	prop_str = ft_itoa(prop);
	msg = ft_strjoin(txt, prop_str);
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, msg);
	free(msg);
	free(prop_str);
}

void	print_mapinfo_bool(t_mrt mrt, const char *txt, bool prop, int *i)
{
	char	*prop_str;
	char	*msg;

	if (prop == true)
		prop_str = ft_strdup("true");
	else
		prop_str = ft_strdup("false");
	msg = ft_strjoin(txt, prop_str);
	print_menu_text(mrt, 30, 20 + (++(*i)) * 15, msg);
	free(msg);
	free(prop_str);
}
