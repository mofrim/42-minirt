/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:46:04 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/17 08:39:02 by fmaurer          ###   ########.fr       */
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
# include "mtrx.h"

/********** Consts. **********/

# include "constants.h"

/********** The Objects. **********/

# include "objects.h"

/********** Parsing. **********/

# include "parser.h"

/********** Colors. **********/

# include "colors.h"

/********** XPM. **********/

# include "xpm.h"

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
	t_xvar			*mlx;
	t_win_list		*win;
	t_scene			*scene;
	t_xpm_canvas	*xc;
}	t_mrt;

/* Directions for moving the camera. */
typedef enum e_dirs
{
	LEFT,
	RIGHT,
	FORTH,
	BACK
}	t_dirs;

/* The hp = hitpoint struct. Holds the surfaces color (scolr) and the final
 * color (fcolr). The scolr is used in the calculations to determine which
 * wavelengths aka colors will be reflected from the surface. All contributions
 * by any lights will be saved in the fcolr member which is returned by
 * calculate_lights(). */
typedef struct s_hpcolr
{
	t_colr	scolr;
	t_colr	fcolr;
}	t_hpcolr;

/********** General functions. **********/

t_mrt		*init_mrt(char *scene_filename);
void		setup_camera(t_camera *cam, t_scene scene);
void		setup_scene(t_scene *scene);
bool		is_cam_inside_obj(t_camera cam, t_scene scene);

/********** File and Scene Handling **********/

char		*read_file(char *filename);
void		test_colors(void);
bool		has_minimum_required_elements(char *content);
t_xpm_canvas	*init_xpm_canvas(t_xvar *mlx);

/********** Debug functions. **********/

void		debug_token(t_token *token, const char *message);
void		debug_camera(t_camera *cam);
void		debug_ambient_light(t_amb_light *alight);
void		debug_sphere(t_sphere *sphere);
void		debug_plane(t_plane *plane);
void		debug_cylinder(t_cylinder *cylinder);
void		debug_light(t_light *light);
void		debug_objects(t_objlst *objects);

/********** Utils. **********/

int			rgb_to_int(char *rgbstr);
t_colr		rgb_to_tcolr(char *rgbstr);
void		int_to_rgb(int rgb_arr[3], int rgb_num);
void		put_pixel_win(t_mrt	mrt, t_pxl pos, char *colr);
void		put_pixel_canvas(t_mrt	mrt, t_pxl pos, char *colr);
void		put_pixel_canvas_rt(t_mrt mrt, t_pxl pos, t_colr pxlcolr);
void		put_string(t_mrt mrt, t_pxl pos, char *colr, char *txt);
void		print_scene(t_scene scene);
int			tcolr_to_int(t_colr colr);
t_colr		int_to_tcolr(int int_colr);
void		error_exit(char *msg);
void		print_errmsg(char *msg);
void		exit_with_errmsg(char *msg);
void		nullcheck(void *p, char *msg);
void		cleanup_mrt(t_mrt *mrt);
double		ft_atof(const char *str);

/********** Math utils. **********/

int			rad2deg_int(double rad);
t_mtrx		get_rotmtrx(t_v3 orient);
t_mtrx		cam_get_new_rot(t_mtrx	oldrot, double x_ang, double y_ang);
t_v3		cam_get_new_pos(t_camera *cam, t_dirs dir, double step);
t_v3		cam_update_orient(t_camera cam);

/********** UI & Event Handlers. **********/

int			close_btn_handler(t_mrt *mrt);
int			kbd_input_handler(int key, t_mrt *mrt);
int			key_press_handler(int key, t_mrt *mrt);
void		show_sidebar(t_mrt mrt);
void		redraw_win(t_mrt mrt);

/********** Trace the rays. **********/

void		raytrace(t_mrt mrt);
double		intersect_ray_single_obj(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
				t_objlst *obj);
t_intersec	intersect_ray_objs(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
				t_objlst *objs);
t_colr		get_object_colr(t_scene scene, t_objlst *close_obj, t_v3 hitpoint);
t_colr		calculate_lights(t_scene scene, t_v3 hitpoint, t_v3 n,
				t_objlst obj);

double		sphere_intersect_ray(t_v3 cam_pos, t_v3 ray_dir, t_ray_minmax rp,
				t_sphere *sphere);
t_colr		sphere_get_colr(t_scene scene, t_objlst sobj, t_v3 hitpoint);

double		circle_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
				t_circle circle);
t_colr		circle_get_colr(t_scene scene, t_objlst cobj, t_v3 hitpoint);
t_colr		colr_add_amblight(t_colr c, t_colr l);

double		triangle_intersect_ray(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
				t_triangle tri);
t_colr		triangle_get_colr(t_scene scene, t_objlst tobj, t_v3 hitpoint);

/********** Color stuff. **********/

void		colr_print(t_colr c, char *name);
t_colr		colr_mult(t_colr c, double i);
t_colr		colr_add_light(t_colr c, t_colr l);
t_colr		colr_get_darkest(t_colr c);
t_colr		colr_apply_intns(t_colr c);
t_colr		hp_add_alight(t_colr sc, t_colr al);
t_colr 		hp_add_pointlight(t_hpcolr hp, t_colr light_colr);
t_colr		colr_add_colr(t_colr c1, t_colr c2);

/********** Do stuff. **********/

void		draw_axis(t_mrt mrt);
void		do_stuff(t_mrt mrt);

#endif
