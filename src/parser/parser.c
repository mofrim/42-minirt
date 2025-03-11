/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/11 19:09:21 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Create a new parser
t_parser *parser_new(Tokenizer *tokenizer)
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
    Token     *token;
    t_objlst  *objlst;

    scene = malloc(sizeof(t_scene));
    if (!scene)
        return (NULL); // Handle allocation error
    scene->objects = NULL; // Initialize objects list

    while ((token = tokenizer_next(parser->tokenizer)) != NULL)
    {
        if (token->type == TOKEN_TYPE_KEYWORD)
        {
            if (strcmp(token->value, "A") == 0)
                scene->alight = parse_ambient_light(parser);
            else if (strcmp(token->value, "C") == 0)
                scene->cam = parse_camera(parser);
            else if (strcmp(token->value, "L") == 0)
            {
                objlst = objlst_new(LIGHT, parse_light(parser));
                objlst_add_back(&scene->objects, objlst);
            }
            else if (strcmp(token->value, "sp") == 0)
            {
                objlst = objlst_new(SPHERE, parse_sphere(parser));
                objlst_add_back(&scene->objects, objlst);
            }
            else if (strcmp(token->value, "pl") == 0)
            {
                objlst = objlst_new(PLANE, parse_plane(parser));
                objlst_add_back(&scene->objects, objlst);
            }
            else if (strcmp(token->value, "cy") == 0)
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

// Parse an ambient light
t_amb_light parse_ambient_light(t_parser *parser)
{
    t_amb_light amb_light;

    amb_light.ratio = parse_number(parser);
    amb_light.colr = parse_color(parser);
    return amb_light;
}

// Parse a camera
t_camera parse_camera(t_parser *parser)
{
    t_camera camera;

    camera.pos = parse_point(parser);
    camera.orient = parse_vector(parser);
    camera.fov = parse_number(parser);
    return camera;
}

// Parse a light
t_light *parse_light(t_parser *parser)
{
    t_light *light = malloc(sizeof(t_light));

    if (!light)
        return (NULL); // Handle allocation error
    light->pos = parse_point(parser);
    light->bright = parse_number(parser);
    light->colr = parse_color(parser);
    return light;
}

// Parse a sphere
t_sphere *parse_sphere(t_parser *parser)
{
    t_sphere *sphere = malloc(sizeof(t_sphere));

    if (!sphere)
        return (NULL); // Handle allocation error
    sphere->center = parse_point(parser);
    sphere->r_squared = parse_number(parser);
    sphere->colr = parse_color(parser);
    return sphere;
}

// Parse a plane
t_plane *parse_plane(t_parser *parser)
{
    t_plane *plane = malloc(sizeof(t_plane));

    if (!plane)
        return (NULL); // Handle allocation error
    plane->pop = parse_point(parser);
    plane->normal = parse_vector(parser);
    plane->colr = parse_color(parser);
    return plane;
}

// Parse a cylinder
t_cylinder *parse_cylinder(t_parser *parser)
{
    t_cylinder *cylinder = malloc(sizeof(t_cylinder));

    if (!cylinder)
        return (NULL); // Handle allocation error
    cylinder->center = parse_point(parser);
    cylinder->axis = parse_vector(parser);
    cylinder->radius = parse_number(parser);
    cylinder->height = parse_number(parser);
    cylinder->colr = parse_color(parser);
    return cylinder;
}

// Helper functions to parse numbers, points, vectors, and colors

// Helper function to parse coordinates from a string like "-50.0,0,20"
t_v3 parse_coordinates(char *str)
{
    t_v3 coords;
    char **parts;

    parts = ft_split(str, ',');
    if (!parts)
    {
        //handle allocation error
    }
    coords.x

}

// Parse a point
t_v3 parse_point(t_parser *parser)
{
    t_token *token;
    
    token = tokenizer_next(parser->tokenizer);

    if (token->type != TOKEN_TYPE_IDENTIFIER)
    {
        // Handle error: Expected identifier
    }

    return parse_coordinates(token->value);
}

// Parse a vector


// Parse color tokens
t_colr parse_color(t_parser *parser)
{
    t_colr color;
    char **parts;
    t_token *token;

    token = tokenizer_next(parser->tokenizer);

    if (token->type != TOKEN_TYPE_IDENTIFIER)
    {
        // handle identifier errors != expected
    }

    parts = ft_split(token->value, ',');
    if (!parts)
    {
        //handle allocation errors 
    }

    color.r = ft_atoi(parts[0]);
    color.g = ft_atoi(parts[1]);
    color.b = ft_atoi(parts[2]);

    free_parts(parts);
    return (color);
}