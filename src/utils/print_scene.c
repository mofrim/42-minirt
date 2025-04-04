/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:43:57 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/04 11:31:37 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static void	print_cam(t_camera cam)
// {
// 	printf("  pos=(%f,%f,%f), look_at=(%f,%f,%f), fov=%f\n",
// 		cam.pos.x, cam.pos.y, cam.pos.z,
// 		cam.orient.x, cam.orient.y, cam.orient.z, cam.fov);
// }

// JUST FOR DEBUG PURPOSES
static void print_debug(t_scene scene)
{
    printf("\n=== Scene Debug Info ===\n");
    
    // Print camera info
    if (scene.cam)
    {
        printf("Camera:\n");
        printf("  Position: (%f, %f, %f)\n", scene.cam->pos.x, scene.cam->pos.y, scene.cam->pos.z);
        printf("  Direction: (%f, %f, %f)\n", scene.cam->orient.x, scene.cam->orient.y, scene.cam->orient.z);
        printf("  FOV: %f radians\n", scene.cam->fov);
        printf("  View width: %f\n", scene.cam->view_width);
    }
    else
    {
        printf("No camera defined!\n");
    }
    
    // Print ambient light info
    if (scene.alight)
    {
        printf("Ambient Light:\n");
        printf("  Brightness: %f\n", scene.alight->bright);
        printf("  Color: (%d, %d, %d)\n", scene.alight->colr.r, scene.alight->colr.g, scene.alight->colr.b);
    }
    else
    {
        printf("No ambient light defined!\n");
    }
    
    // Print objects
    printf("Objects:\n");
    int count = 0;
    t_objlst *current = scene.objects;
    while (current)
    {
        count++;
        switch (current->type)
        {
            case LIGHT:
            {
                t_light *light = (t_light *)current->obj;
                printf("  Light %d:\n", count);
                printf("    Position: (%f, %f, %f)\n", light->pos.x, light->pos.y, light->pos.z);
                printf("    Brightness: %f\n", light->bright);
                printf("    Color: (%d, %d, %d)\n", light->colr.r, light->colr.g, light->colr.b);
                break;
            }
            case SPHERE:
            {
                t_sphere *sphere = (t_sphere *)current->obj;
                printf("  Sphere %d:\n", count);
                printf("    Center: (%f, %f, %f)\n", sphere->center.x, sphere->center.y, sphere->center.z);
                printf("    Radius: %f\n", sphere->r);
                printf("    Color: (%d, %d, %d)\n", sphere->colr.r, sphere->colr.g, sphere->colr.b);
                break;
            }
            case PLANE:
            {
                t_plane *plane = (t_plane *)current->obj;
                printf("  Plane %d:\n", count);
                printf("    Point: (%f, %f, %f)\n", plane->pop.x, plane->pop.y, plane->pop.z);
                printf("    Normal: (%f, %f, %f)\n", plane->normal.x, plane->normal.y, plane->normal.z);
                printf("    Color: (%d, %d, %d)\n", plane->colr.r, plane->colr.g, plane->colr.b);
                break;
            }
            case CYLINDER:
            {
                t_cylinder *cylinder = (t_cylinder *)current->obj;
                printf("  Cylinder %d:\n", count);
                printf("    Center: (%f, %f, %f)\n", cylinder->center.x, cylinder->center.y, cylinder->center.z);
                printf("    Axis: (%f, %f, %f)\n", cylinder->axis.x, cylinder->axis.y, cylinder->axis.z);
                printf("    Radius: %f\n", cylinder->radius);
                printf("    Height: %f\n", cylinder->height);
                printf("    Color: (%d, %d, %d)\n", cylinder->colr.r, cylinder->colr.g, cylinder->colr.b);
                break;
            }
            case CIRCLE:
            {
                t_circle *circle = (t_circle *)current->obj;
                printf("  Circle %d:\n", count);
                printf("    Center: (%f, %f, %f)\n", circle->center.x, circle->center.y, circle->center.z);
                printf("    Normal: (%f, %f, %f)\n", circle->normal.x, circle->normal.y, circle->normal.z);
                printf("    Radius: %f\n", circle->r);
                printf("    Color: (%d, %d, %d)\n", circle->colr.r, circle->colr.g, circle->colr.b);
                break;
            }
            default:
                printf("  Unknown object type %d\n", current->type);
        }
        current = current->next;
    }
    printf("Total objects: %d\n", count);
    printf("=== End Scene Debug Info ===\n\n");
}


/**
 * Print the contents of the scene struct
 *
 * Only for debugging and info purpose.
 */
void	print_scene(t_scene scene)
{
	print_debug(scene);
}



void debug_parsed_scene(t_scene *scene)
{
    int	count = 0;
    t_objlst	*current;

	count = 0;
	current = scene->objects;
    printf("\n=== Parsed Scene Debug ===\n");
    if (!scene)
    {
        printf("Scene is NULL!\n");
        return;
    }
    if (scene->cam)
        printf("Camera found\n");
    else
        printf("No camera found\n");
    if (scene->alight)
        printf("Ambient light found\n");
    else
        printf("No ambient light found\n");
    while (current)
    {
        count++;
        current = current->next;
    }
    printf("Number of objects: %d\n=== End Parsed Scene Debug ===\n\n", count);
}

void debug_token(t_token *token, const char *message)
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
