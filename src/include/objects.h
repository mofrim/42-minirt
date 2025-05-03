/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:36:20 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/03 12:37:26 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "v3.h"
# include "mtrx.h"
# include <stdint.h>
# include <stdbool.h>

/* The RGB color struct. I would like to use the l = brightness value like
 * according to the HSL = Hue Saturation Lightness - color model. This means:
 * - l = 0 -> color is black
 * - 0 < l <= 0.5 -> colr is darker or at normal brightness at l = 0.5
 * - 0.5 < l <= 1.0 -> colr is brighter with being white at l = 1.0 */
typedef struct s_colr
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	float	i;
}	t_colr;

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
 */
typedef struct s_hyper
{
	t_v3	center;
	t_v3	axis;
	t_mtrx	A;
	double	a;
	double	b;
	double	c;
	float	h;
	float	rcaps;
	double  hby2;
	t_colr	colr;
}	t_hyper;

typedef struct s_sphere
{
	t_v3	center;
	double	r;
	double	r_squared;
	t_colr	colr;
}	t_sphere;

typedef struct s_cylinder
{
	t_v3	center;
	t_v3	axis;
	double	radius;
	double	height;
	t_colr	colr;
}	t_cylinder;

/* pop = Point On Plane :) */
typedef struct s_plane
{
	t_v3	pop;
	t_v3	normal;
	t_colr	colr;
}	t_plane;

typedef struct s_circle
{
	double	r;
	double	r2;
	t_v3	normal;
	t_v3	center;
	t_colr	colr;
	bool	hycap;
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
typedef struct s_camera {
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

/********** Objlst llist funcs. **********/

t_objlst	*objlst_new(t_objtype type, void *obj);
t_objlst	*objlst_last(t_objlst *head);
void		objlst_add_back(t_objlst **head, t_objlst *newend);
void		objlst_clear(t_objlst *lst);
void		objlst_print(t_objlst *lst);

#endif
