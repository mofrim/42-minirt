/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:43:57 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/08 09:24:50 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_cam(t_camera cam)
{
	printf("  [-1] cam { pos=(%f,%f,%f), orient=(%f,%f,%f), fov=%f }\n",
		cam.pos.x, cam.pos.y, cam.pos.z,
		cam.orient.x, cam.orient.y, cam.orient.z, cam.fov);
}

void	print_scene(t_scene sc)
{
	printf("the scene:\n");
	if (sc.cam)
		print_cam(*sc.cam);
	objlst_print(sc.objects);
}

void	debug_token(t_token *token, const char *message)
{
	if (!token)
	{
		printf("DEBUG TOKEN %s: NULL token\n", message);
		return ;
	}
	if (token->type == TOKEN_TYPE_KEYWORD)
		printf("DEBUG TOKEN %s: KEYWORD: '%s'\n", message, token->u_value.str);
	else if (token->type == TOKEN_TYPE_NUMBER)
		printf("DEBUG TOKEN %s: NUMBER: %f\n", message, token->u_value.num);
	else if (token->type == TOKEN_TYPE_IDENTIFIER)
		printf("DEBUG TOKEN %s: IDENTIFIER: '%s'\n", message,
			token->u_value.str);
	else if (token->type == TOKEN_TYPE_SYMBOL)
		printf("DEBUG TOKEN %s: SYMBOL: '%s'\n", message, token->u_value.str);
	else if (token->type == TOKEN_TYPE_V3)
		printf("DEBUG TOKEN %s: V3: '%s'\n", message, token->u_value.str);
	else
		printf("DEBUG TOKEN %s: UNKNOWN TYPE\n", message);
}
