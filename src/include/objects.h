/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:36:20 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/02 15:07:02 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"
# include "v3.h"
# include "mtrx.h"
# include <stdint.h>

/* The RGB color struct. */
typedef struct s_colr
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_colr;

/* Object structs */
typedef enum e_obj
{
	LIGHT,
	PLANE,
	SPHERE,
	CYLINDER,
	CIRCLE
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
}	t_circle;

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
}	t_camera;

/* The objects linked list. */
typedef struct s_objlst
{
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
