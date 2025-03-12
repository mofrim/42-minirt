/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/12 16:32:25 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Create a new parser
t_parser *parser_new(t_tokenizer *tokenizer)
{
    t_parser *parser = malloc(sizeof(t_parser));
    if (!parser)
        return NULL;
    parser->tokenizer = tokenizer;
    return parser;
}

// Parse the stream of tokens and return the scene
t_scene *parser_parse(t_parser *parser)
{
    t_scene  *scene;
    t_token     *token;
    t_objlst  *objlst;

    scene = malloc(sizeof(t_scene));
    if (!scene)
        return (NULL); // Handle allocation error
    scene->objects = NULL; // Initialize objects list
    scene->alight = NULL;
    scene->cam = NULL;

    while ((token = tokenizer_next(parser->tokenizer)) != NULL)
    {
        if (token->type == TOKEN_TYPE_KEYWORD)
        {
            if (strcmp(token->u_value.str, "A") == 0)
                scene->alight = parse_ambient_light(parser);
            else if (strcmp(token->u_value.str, "C") == 0)
                scene->cam = parse_camera(parser);
            else if (strcmp(token->u_value.str, "L") == 0)
            {
                objlst = objlst_new(LIGHT, parse_light(parser));
                objlst_add_back(&scene->objects, objlst);
            }
            else if (strcmp(token->u_value.str, "sp") == 0)
            {
                objlst = objlst_new(SPHERE, parse_sphere(parser));
                objlst_add_back(&scene->objects, objlst);
            }
            else if (strcmp(token->u_value.str, "pl") == 0)
            {
                objlst = objlst_new(PLANE, parse_plane(parser));
                objlst_add_back(&scene->objects, objlst);
            }
            else if (strcmp(token->u_value.str, "cy") == 0)
            {
                objlst = objlst_new(CYLINDER, parse_cylinder(parser));
                objlst_add_back(&scene->objects, objlst);
            }
            else
            {
                // Handle invalid keyword
            }
        }
        else
        {
            // Handle unexpected token
        }
        token_free(token);
    }
    return scene;
}

// Free the parser
void parser_free(t_parser *parser)
{
    free(parser);
}

// Parse the ambient light
t_amb_light *parse_ambient_light(t_parser *parser)
{
    t_amb_light *amb_light;
    amb_light = malloc(sizeof(t_amb_light));

    if (!amb_light)
        return (NULL); // Handle allocation error
    amb_light->ratio = parse_number(parser->tokenizer);
    amb_light->colr = parse_color(parser);
    return amb_light;
}

// Parse the camera
t_camera *parse_camera(t_parser *parser)
{
    t_camera *camera;
    camera = malloc(sizeof(t_camera));

    if (!camera)
        return (NULL); // Handle allocation error
    camera->pos = parse_v3(parser);
    camera->orient = parse_v3(parser);
    camera->fov = parse_number(parser->tokenizer);
    return camera;
}

// Parse a light
t_light *parse_light(t_parser *parser)
{
    t_light *light = malloc(sizeof(t_light));

    if (!light)
        return (NULL); // Handle allocation error
    light->pos = parse_v3(parser);
    light->bright = parse_number(parser->tokenizer);
    light->colr = parse_color(parser);
    return light;
}

// Parse a sphere
t_sphere *parse_sphere(t_parser *parser)
{
    t_sphere *sphere = malloc(sizeof(t_sphere));

    if (!sphere)
        return (NULL); // Handle allocation error
    sphere->center = parse_v3(parser);
    sphere->r_squared = parse_number(parser->tokenizer);
    sphere->colr = parse_color(parser);
    return sphere;
}

// Parse a plane
t_plane *parse_plane(t_parser *parser)
{
    t_plane *plane = malloc(sizeof(t_plane));

    if (!plane)
        return (NULL); // Handle allocation error
    plane->pop = parse_v3(parser);
    plane->normal = parse_v3(parser);
    plane->colr = parse_color(parser);
    return plane;
}

// Parse a cylinder
t_cylinder *parse_cylinder(t_parser *parser)
{
    t_cylinder *cylinder = malloc(sizeof(t_cylinder));

    if (!cylinder)
        return (NULL); // Handle allocation error
    cylinder->center = parse_v3(parser);
    cylinder->axis = parse_v3(parser);
    cylinder->radius = parse_number(parser->tokenizer);
    cylinder->height = parse_number(parser->tokenizer);
    cylinder->colr = parse_color(parser);
    return cylinder;
}

// Helper functions to parse numbers and colors

// Parse color tokens
t_colr parse_color(t_parser *parser)
{
    t_colr color;
    t_token *token;
    // Parse r
    token = tokenizer_next(parser->tokenizer);
    if (!token || token->type != TOKEN_TYPE_NUMBER) {
        // Handle error
    }
    color.r = (int)token->u_value.num;
    token_free(token);
    // Parse g
    token = tokenizer_next(parser->tokenizer);
    if (!token || token->type != TOKEN_TYPE_NUMBER) {
        // Handle error
    }
    color.g = (int)token->u_value.num;
    token_free(token);
    // Parse b
    token = tokenizer_next(parser->tokenizer);
    if (!token || token->type != TOKEN_TYPE_NUMBER) {
        // Handle error
    }
    color.b = (int)token->u_value.num;
    token_free(token);
    return color;
}

// Helper function to parse coordinates from a string like "-50.0,0,20"
t_v3 parse_v3(t_parser *parser)
{
    t_v3 v3;
    t_token *token;
    // Parse x
    token = tokenizer_next(parser->tokenizer);
    if (!token || token->type != TOKEN_TYPE_NUMBER) {
        // Handle error
    }
    v3.x = token->u_value.num;
    token_free(token);
    // Parse y
    token = tokenizer_next(parser->tokenizer);
    if (!token || token->type != TOKEN_TYPE_NUMBER) {
        // Handle error
    }
    v3.y = token->u_value.num;
    token_free(token);
    // Parse z
    token = tokenizer_next(parser->tokenizer);
    if (!token || token->type != TOKEN_TYPE_NUMBER) {
        // Handle error
    }
    v3.z = token->u_value.num;
    token_free(token);
    return (v3);
}

void token_free(t_token *token)
{
    if (token) {
        if (token->type == TOKEN_TYPE_KEYWORD ||
            token->type == TOKEN_TYPE_IDENTIFIER ||
            token->type == TOKEN_TYPE_SYMBOL) {
            free(token->u_value.str);
        }
        free(token);
    }
}
