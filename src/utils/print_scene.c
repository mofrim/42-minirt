/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:43:57 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/26 10:46:42 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_cam(t_camera cam)
{
	printf("  [-1] cam  pos=(%f,%f,%f), orient=(%f,%f,%f), fov=%f }\n",
		cam.pos.x, cam.pos.y, cam.pos.z,
		cam.orient.x, cam.orient.y, cam.orient.z, cam.fov);
	printf("            %.2f,%.2f,%.2f %.2f,%.2f,%.2f %d\n",
		cam.pos.x, cam.pos.y, cam.pos.z,
		cam.orient.x, cam.orient.y, cam.orient.z, rad2deg_int(cam.fov));
}

void	print_scene(t_scene sc)
{
	printf("the scene:\n");
	if (sc.cam)
		print_cam(*sc.cam);
	objlst_print(sc.objects);
}
