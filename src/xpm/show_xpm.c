/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:07:36 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/23 14:28:35 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	show_xpm(t_mrt mrt)
{
	t_img	*img;
	int		width;
	int		height;

	img = mlx_xpm_file_to_image(mrt.mlx,
			"./images/snowflake.xpm", &width, &height);
	if (img)
		mlx_put_image_to_window(mrt.mlx, mrt.win, img, 0, 500);
}
