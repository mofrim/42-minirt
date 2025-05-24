/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:14:21 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/24 16:35:58 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include <stdbool.h>
# include "keycodes.h"

typedef struct s_mrt		t_mrt;
typedef struct s_xpm_canvas	t_xpm_canvas;

typedef struct s_sidebar_theme
{
	int	sep_colr;
	int	txt_colr;
	int	head_colr;
	int	title_colr;
}	t_sidebar_theme;

t_sidebar_theme	set_sidethm_default(void);
t_sidebar_theme	set_sidethm_black(void);
int				close_btn_handler(t_mrt *mrt);
int				kbd_release_handler(int key, t_mrt *mrt);
int				kbd_press_handler(int key, t_mrt *mrt);
void			show_sidebar(t_mrt mrt);
void			clear_sidebar(t_mrt *mrt);
void			redraw_win(t_mrt mrt, bool print_msg);
int				export_ppm(t_xpm_canvas xc, int canvas_width);
void			draw_axis(t_mrt mrt);
void			launch_ui(t_mrt mrt);

#endif
