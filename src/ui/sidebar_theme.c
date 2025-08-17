/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar_theme.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:39:02 by fmaurer           #+#    #+#             */
/*   Updated: 2025/08/17 22:01:23 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ui.h"

/* Set the default sidebar theme. */
t_sidebar_theme	set_sidethm_default(void)
{
	return ((t_sidebar_theme){
		rgb_to_int(DARK_CYAN),
		rgb_to_int(MEDIUM_SEA_GREEN),
		rgb_to_int(LIGHT_SEA_GREEN),
		rgb_to_int(GREEN),
		rgb_to_int(GRAY),
		rgb_to_int(LIGHT_SLATE_GRAY)
	});
}

t_sidebar_theme	set_sidethm_black(void)
{
	return ((t_sidebar_theme){0, 0, 0, 0, 0, 0});
}
