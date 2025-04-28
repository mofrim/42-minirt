/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:36:20 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/28 14:54:13 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"
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
	TRIANGLE
}	t_objtype;

/* WARNING: the subject specifies that the *diameter* will be specified in the
 * scene.rt... still the radius is the number we will calculate with. this
 * means during parsing we need to devide the diameter read from the file by 2!
 */
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
	t_v3	p1;		//center of the first cap circle
	t_v3	p2;		//center of the second cap circle
	t_v3	axis;
	double	r;		//radius
	double	r_squared;
	double	height;	// p2 - p1 basically
	t_colr	colr;
}	t_cylinder;

// Helper struct for quadratic equation results
typedef struct s_quad_sol {
    double t1;
    double t2;
    double disc; // Discriminant
} t_quad_sol;

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

typedef struct s_amb_light
{
	double	bright;
	t_colr	colr;
}	t_amb_light;

typedef struct s_light
{
	t_v3	pos;
	t_colr	colr;
	double	bright;
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
