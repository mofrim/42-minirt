/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:22:49 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/11 18:26:32 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

// Define the different types of nodes in the AST
typedef enum {
    NODE_TYPE_SCENE,
    NODE_TYPE_AMBIENT_LIGHT,
    NODE_TYPE_CAMERA,
    NODE_TYPE_LIGHT,
    NODE_TYPE_SPHERE,
    NODE_TYPE_PLANE,
    NODE_TYPE_CYLINDER,
} NodeType;

// Define the structure of a node in the AST
typedef struct s_node {
    NodeType    type;
    t_camera    camera;
    t_amb_light alight;
    t_sphere    sphere;
    t_plane     plane;
    t_cylinder  cylinder;
    struct s_node *next; // For sibling nodes (no need for children)
}   t_node;

// Define the parser
typedef struct s_parser {
    Tokenizer *tokenizer;
} t_parser;

// Create a new parser
t_parser *parser_new(Tokenizer *tokenizer);

// Parse the stream of tokens and return the AST
t_node *parser_parse(t_parser *parser);

// Free the parser
void parser_free(t_parser *parser);

#endif