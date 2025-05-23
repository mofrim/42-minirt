/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:36:20 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/23 00:13:46 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "v3.h"
# include "mtrx.h"
# include "colors.h"
# include <stdbool.h>

/* For t_img. */
# include "../minilibx-linux/mlx_int.h"

typedef struct s_mrt	t_mrt;

/* The RGB color struct. I would like to use the l = brightness value like
 * according to the HSL = Hue Saturation Lightness - color model. This means:
 * - l = 0 -> color is black
 * - 0 < l <= 0.5 -> colr is darker or at normal brightness at l = 0.5
 * - 0.5 < l <= 1.0 -> colr is brighter with being white at l = 1.0 */
/* Object structs */
typedef enum e_obj
{
	LIGHT,
	PLANE,
	SPHERE,
	CYLINDER,
	CIRCLE,
	TRIANGLE,
	HYPER
}	t_objtype;

/* We will only support a one-sheet hyperbolid of revolution, i.e. one that can
 * be construted by rotating a hyperbola about the axis. This implies a == b in
 * its formula:
 *
 * 		x**2/a**2 + y**2/b**2 - z**2/c**2 = 1
 *
 * if a != b the caps would be ellipses and not circles. this we will skip in
 * our minirt.
 * hym := "Hyperbolo Matrix".
 */
typedef struct s_hyper
{
	t_v3	center;
	t_v3	axis;
	t_mtrx	hym;
	double	ab;
	double	c;
	double	h;
	double	rcaps;
	double	hby2;
	t_colr	colr;
	float	spec;
	int		checker;
	float	checker_scale;
	char	*tex_file;
	t_img	*tex_img;
}	t_hyper;

typedef struct s_sphere
{
	t_v3	center;
	double	r;
	double	r_squared;
	t_colr	colr;
	float	spec;
	char	*tex_file;
	char	*nmap_file;
	t_img	*tex_img;
	t_img	*nmap_img;
	bool	bump;
	float	bumpiness;
	bool	checker;
	float	checker_scale;
}	t_sphere;

typedef struct s_cylinder
{
	t_v3	center;
	t_v3	p1;		//center of the first cap circle
	t_v3	p2;		//center of the second cap circle
	t_v3	axis;
	double	r;		//radius
	double	r_squared;
	double	height;	// p2 - p1 basically
	t_colr	colr;
	float	spec;
}	t_cylinder;

// Helper struct for quadratic equation results
typedef struct s_quad_sol
{
	double	t1;
	double	t2;
	double	disc;
}	t_quad_sol;

/* pop = Point On Plane :) */
typedef struct s_plane
{
	t_v3	pop;
	t_v3	normal;
	t_colr	colr;
	float	spec;
	bool	checker;
	float	checker_scale;

}	t_plane;

typedef struct s_circle
{
	double	r;
	double	r2;
	t_v3	normal;
	t_v3	center;
	t_colr	colr;
	float	spec;
}	t_circle;

/* potdn = PointOnTriangleDotN convenience variable to speed up intersection
 * calc. */
// TODO: also do this for circles and planes.
typedef struct s_triangle
{
	t_v3	a;
	t_v3	b;
	t_v3	c;
	t_v3	ab;
	t_v3	ac;
	t_v3	bc;
	t_v3	normal;
	double	potdn;
	double	area;
	t_colr	colr;
	float	spec;
}	t_triangle;

typedef struct s_alight
{
	double	bright;
	t_colr	colr;
}	t_alight;

typedef struct s_light
{
	t_v3	pos;
	t_colr	colr;
}	t_light;

/* Camera struct. */
typedef struct s_camera
{
	t_v3	pos;
	t_v3	orient;
	t_mtrx	rot;
	double	fov;
	double	view_width;
	double	cvr;
	bool	is_inside_obj;
}	t_camera;

/* The objects linked list. */
typedef struct s_objlst
{
	int				id;
	t_objtype		type;
	void			*obj;
	struct s_objlst	*next;
}	t_objlst;

/* The intersection ray param and the obj in one struct \o/ */
typedef struct s_intersec
{
	double		t;
	t_objlst	*obj;
}	t_intersec;

/* The struct holding tmin and tmax as params for intersection funcs. */
typedef struct s_ray_minmax
{
	double	tmin;
	double	tmax;
}	t_ray_minmax;

/* The hp = hitpoint struct.
 *
 * Members:
 * - loc = hitpoint location vector
 * - normal = surface normal at hit
 * - cam2hp = cam to hit vec for specular refl calc
 * - scolr = surfaces original color from scenefile
 * - fcolr = surfaces final colr after calculate_lights
 * - spec = the specular reflection exponent
 *
 * The scolr is used in the calculations to determine which wavelengths aka
 * colors will be reflected from the surface. All contributions by any lights
 * will be saved in the fcolr member which is returned by calculate_lights().
 */
typedef struct s_hp
{
	t_v3	loc;
	t_v3	normal;
	t_v3	cam2hp;
	t_colr	scolr;
	t_colr	fcolr;
	float	spec;
}	t_hp;

/********** Objlst llist funcs. **********/

t_objlst	*objlst_new(t_objtype type, void *obj);
t_objlst	*objlst_last(t_objlst *head);
void		objlst_add_back(t_objlst **head, t_objlst *newend);
void		objlst_clear(t_mrt mrt, t_objlst *lst);
void		objlst_print(t_objlst *lst);

/********** Cylinder Utilities **********/

// Parameters for cylinder intersection calculations.
typedef struct s_cyl_intersect_params
{
	t_v3			origin;
	t_v3			ray_dir;
	t_cylinder		*cyl;
	t_ray_minmax	rp;
}	t_cyl_intersect_params;

// Coefficients for the quadratic equation
typedef struct s_quad_coeffs
{
	double	a;
	double	b;
	double	c;
}	t_quad_coeffs;

/*
 * Structure to hold parameters for normal calculation at a hit point.
 * cyl: Pointer to the cylinder object.
 * hit_point: The 3D coordinate of the intersection.
 * incident_ray_dir: Direction of the ray that hit the cylinder.
 * is_cap_hit: Flag indicating if the hit was on a cap (useful for normal).
 * cap_normal_idx: If is_cap_hit, indicates which cap (e.g., 0 for p1, 1 for p2).
*/
typedef struct s_cyl_normal_params
{
	t_cylinder	*cyl;
	t_v3		hit_point;
	t_v3		incident_ray_dir;
	int			is_cap_hit;
	int			cap_normal_idx;
}	t_cyl_normal_params;

// FIXME: move all object funcs in here
/* From cylinder_body.c */
double		calculate_body_intersection_t(t_cyl_intersect_params *params);

/* From cylinder_caps.c */
double		intersect_caps_circles(t_cyl_intersect_params *params);

/* From cylinder_normal.c */
t_v3		calculate_cylinder_normal_at_hit(t_cyl_normal_params *params);

#endif
