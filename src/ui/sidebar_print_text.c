/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar_print_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:21:00 by fmaurer           #+#    #+#             */
/*   Updated: 2025/08/17 22:10:16 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_float_string(double d);

/* Wrapper around mlx_string_put for applying our color. */
void	print_menu_text(t_mrt mrt, int x, int y, char *txt)
{
	mlx_string_put(mrt.mlx, mrt.win, x, y, mrt.side_thm.txt_colr, txt);
}

void	print_keys(t_mrt mrt, int x, int y, char *txt)
{
	char	**txt_split;
	int		i;

	txt_split = ft_split(txt, ':');
	nullcheck(txt_split, "print_menu_txt()");
	i = -1;
	while (++i < 2)
	{
		if (txt_split[i] == NULL)
		{
			ft_freesplit(&txt_split);
			return ;
		}
	}
	mlx_string_put(mrt.mlx, mrt.win, x, y, mrt.side_thm.menu_txt_colr1,
		txt_split[0]);
	mlx_string_put(mrt.mlx, mrt.win, x + 50, y, mrt.side_thm.menu_txt_colr2,
		txt_split[1]);
	ft_freesplit(&txt_split);
}

/* Print a menu header line. */
void	print_menu_header(t_mrt mrt, int x, int y, char *txt)
{
	mlx_string_put(mrt.mlx, mrt.win, x, y, mrt.side_thm.head_colr, txt);
}
