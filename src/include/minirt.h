/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:46:04 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/11 09:48:13 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* all the math... */
# include <math.h>

/* free, malloc */
# include <stdlib.h>

/* read, close */
# include <unistd.h>

/* write */
# include <fcntl.h>

/* perror */
# include <stdio.h>

/* strerror */
# include <string.h>

/* errno */
# include <errno.h>

/* for uint8_t, ... */
# include <stdint.h>

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"

/********** LinalAlg headers. **********/

# include "vec3.h"
# include "v3.h"
# include "ray.h"
# include "mtrx.h"

/********** Consts. **********/

# include "constants.h"

/********** The Objects. **********/

# include "objects.h"

/********** Structs. **********/

/* In principle a 2d vector... */
typedef struct s_v2
{
	double	x1;
	double	x2;
}	t_v2;

/* The scene master struct. */
typedef struct s_scene
{
	t_camera	*cam;
	t_amb_light	*alight;
	t_objlst	*objects;
	int			subsample;
}	t_scene;

/* A pixel on our screen. */
typedef struct s_pxl
{
	int	x;
	int	y;
}	t_pxl;

/* The MiniRT master-struct holding all nesessary data and pointers to struct
 * needed throughout the program. */
typedef struct s_mrt
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_scene		*scene;
}	t_mrt;

/********** General functions. **********/

t_scene	*parse_scene(char *scene_file);
t_mrt	*init_mrt(t_scene *scene);

/********** Utils. **********/

int		rgb_to_int(char *rgbstr);
void	int_to_rgb(int rgb_arr[3], int rgb_num);
void	put_pixel_win(t_mrt	mrt, t_pxl pos, char *colr);
void	put_pixel_canvas(t_mrt	mrt, t_pxl pos, char *colr);
void	put_pixel_canvas_rt(t_mrt mrt, t_pxl pos, t_colr pxlcolr);
void	put_string(t_mrt mrt, t_pxl pos, char *colr, char *txt);
void	print_scene(t_scene scene);
int		tcolr_to_int(t_colr colr);
t_colr	int_to_tcolr(int int_colr);

/********** Math utils. **********/

int		rad2deg_int(double rad);
t_mtrx	get_rotmtrx(t_v3 orient);

/********** UI. **********/

int		close_btn_handler(t_mrt *mrt);
int		kbd_input_handler(int key, t_mrt *mrt);
void	show_sidebar(t_mrt mrt);
void	redraw_win(t_mrt mrt);

/********** Trace the rays. **********/

void	raytrace(t_mrt mrt);
double 	intersect_ray_obj(t_v3 cam_pos, t_v3 ray_dir, t_objlst *obj);
double	intersect_ray_sphere(t_v3 cam_pos, t_v3 d, t_sphere *sphere);
t_colr	get_object_colr(t_scene scene, t_objlst *close_obj, t_v3 hitpoint);
t_colr	colr_mult(t_colr c, double i);

/********** Do stuff. **********/

void	draw_axis(t_mrt mrt);
void	do_stuff(t_mrt mrt);

#endif
