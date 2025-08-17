/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar_print_mapinfo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 22:09:59 by fmaurer           #+#    #+#             */
/*   Updated: 2025/08/17 22:11:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_float_string(double d);
void	print_menu_text(t_mrt mrt, int x, int y, char *txt);

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
