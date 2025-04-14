/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:29:11 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/17 08:35:36 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	init_cam(t_mrt mrt)
// {
// 	t_camera	*cam;

// 	mrt.scene->cam = malloc(sizeof(t_camera));
// 	cam = mrt.scene->cam;
// 	cam->pos = v3_new(0, 3, -3);
// 	cam->orient = v3_new(0, -1, 1.5);
// 	cam->fov = M_PI_4;
// 	cam->rot = get_rotmtrx(v3_get_norm(cam->orient));
// 	cam->view_width = 2 * tan(cam->fov/2);
// 	cam->cvr = cam->view_width / CANVAS_WIDTH;
// 	printf("cam->viewport_width = %lf\n", cam->view_width);
// }

// void setup_camera(t_camera *cam)
// {
// 	if (!cam)
// 		return ;
// 	// set up the rotation matrix
// 	cam->rot = get_rotmtrx(v3_get_norm(cam->orient));

// 	// Calculate view based on fov
// 	cam->view_width = 2 * tan(cam->fov / 2);

// 	//calculate canvas to viewport ratio
// 	cam->cvr = cam->view_width / CANVAS_WIDTH;

// 	ft_printf("cam->viewport_width = %lf\n", cam->view_width);
// }


void	add_circle(t_mrt mrt)
{
	t_circle	*c = malloc(sizeof(t_circle));
	c->center = (t_v3){0, 0, 0};
	c->r = 10;
	c->r2 = c->r * c->r;
	c->normal = v3_get_norm((t_v3){0, 0, -1});
	c->colr = rgb_to_tcolr(DARK_SLATE_BLUE);
	objlst_add_back(&mrt.scene->objects, objlst_new(CIRCLE, c));
}

void	add_triangle(t_mrt mrt)
{
	t_triangle *t0 = malloc(sizeof(t_triangle));
	t0->a = (t_v3){-4,-4,-2};
	t0->b = (t_v3){4,-4,-2};
	t0->c = (t_v3){0,4,-2};
	t0->ab = v3_minus_vec(t0->b, t0->a);
	t0->ac = v3_minus_vec(t0->c, t0->a);
	t0->bc= v3_minus_vec(t0->c, t0->b);
	t0->normal = v3_mult(v3_cross(t0->ab, t0->ac), -1);
	t0->potdn = v3_dot(t0->a, t0->normal);
	t0->area = 0.5 * v3_norm(v3_cross(t0->ab, t0->ac));
	t0->colr = rgb_to_tcolr(ORANGE);
	objlst_add_back(&mrt.scene->objects, objlst_new(TRIANGLE, t0));
}

void	color_test(t_mrt mrt, t_colr colr)
{
	int		x;
	int		y;
	float	i;

	x = -100;
	while (x <= 100)
	{
		y = -100;
		while (y <= 100)
		{
			i = 0.1 * ((y + 100) / 20);
			colr.i = i;
			put_pixel_xpm(mrt.xc, x, y, colr_apply_intns(colr));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.xc->img, SIDEBAR_AREA_X, 0);
}

/* Draw a colored square at the center of the canvas with the color specified as
 * param. Useful for checking correct color display. */
void	color_square(t_mrt mrt, t_colr colr)
{
	int		x;
	int		y;

	x = -100;
	while (x <= 100)
	{
		y = -100;
		while (y <= 100)
			put_pixel_xpm(mrt.xc, x, y++, colr_apply_intns(colr));
		x++;
	}
	mlx_put_image_to_window(mrt.mlx, mrt.win, mrt.xc->img, SIDEBAR_AREA_X, 0);
}

t_colr colr_get_darkest(t_colr c);

void	do_stuff(t_mrt mrt)
{
	// init_scene(mrt);
	show_sidebar(mrt);
	print_scene(*mrt.scene);
	raytrace_xpm(mrt);


	/* Added this for testing correct color display. */

	// t_colr c = colr_get_darkest((t_colr){255,100,100,1});
	// t_colr c = colr_mult((t_colr){255,100,100,1}, 0.1);
	// t_colr c = colr_mult((t_colr){25,0,0,1}, 1);
	// t_colr c = colr_add_light((t_colr){25,25,25,1}, (t_colr){255,0,0,0.1});
	// t_colr c = (t_colr){125,0,0,1};
	// colr_print(c, "c");
	// color_square(mrt, c);
}
