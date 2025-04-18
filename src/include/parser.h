/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:22:49 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/18 21:54:14 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// to prevent cross includes
# include "objects.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

/* Forward declarations from minirt.h */
typedef struct s_scene t_scene;
typedef struct s_mrt t_mrt;

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

// Define the different types of tokens
typedef enum e_tokentype
{
	TOKEN_TYPE_KEYWORD,
	TOKEN_TYPE_V3,
	TOKEN_TYPE_IDENTIFIER,
	TOKEN_TYPE_NUMBER,
	TOKEN_TYPE_SYMBOL,
}	t_tokentype;

// Define the structure of a token
typedef struct s_token
{
	t_tokentype	type;
	union
	{
		char	*str; // For keywords, identifiers, symbols
		double	num; // For numbers
	}	u_value;
}	t_token;

// Define the tokenizer
typedef struct s_tokenizer
{
	char	*input;
	int		pos;
	size_t	len;
}	t_tokenizer;

/********** PARSER FUNCTIONS **********/

// Main parsing functions
int			get_scene_from_parser(t_tokenizer *tokenizer, t_scene *scene);
t_scene		*parse_scene(char *scene_filename, t_mrt *mrt);
t_scene     *init_scene(void);
int			lineparse_scenefile(t_tokenizer *tokenizer, t_scene *scene);

// Token handlers
void        handle_token_keyword(t_tokenizer *tokenizer, t_scene *scene, t_token *token);
void        handle_more_keywords(t_tokenizer *tokenizer, t_scene *scene, t_token *token);

// Object parsers
t_amb_light *parse_ambient_light(t_tokenizer *tokenizer);
t_camera    *parse_camera(t_tokenizer *tokenizer);
t_light     *parse_light(t_tokenizer *tokenizer);
t_colr      parse_color(t_tokenizer *tokenizer, bool *valid);
t_sphere    *parse_sphere(t_tokenizer *tokenizer);
t_plane     *parse_plane(t_tokenizer *tokenizer);
t_cylinder  *parse_cylinder(t_tokenizer *tokenizer);
t_triangle	*parse_triangle(t_tokenizer *tokenizer);
t_circle	*parse_circle(t_tokenizer *tokenizer);

// Parser utilities
t_v3        parse_v3(t_tokenizer *tokenizer, bool *valid);
t_v3        parse_v3_from_parts(char **parts);
double      parse_number(t_tokenizer *tokenizer);
void        free_parts(char **parts);
void        free_parts_helper(char **parts);
char        *read_scenefile(char *filename);
bool        has_rt_ext(char *filename);
bool        validate_color(char **parts, bool *valid);
bool        validate_vector(char **parts, bool *valid);
bool        has_minimum_required_elements(char *content);

/********** TOKENIZER FUNCTIONS **********/

t_tokenizer *tokenizer_new(char *input);
t_token     *tokenizer_next(t_tokenizer *tokenizer);
void        token_free(t_token *token);

// Token type parsers
t_token     *parse_coordinate(t_tokenizer *tokenizer);
t_token     *parse_identifier(t_tokenizer *tokenizer);
t_token     *parse_number_token(t_tokenizer *tokenizer);
t_token     *parse_symbol_token(t_tokenizer *tokenizer);

// Helper functions for tokenizing
void        skip_whitespace(t_tokenizer *tokenizer);
int         is_coordinate(t_tokenizer *tokenizer);
void        skip_sign(t_tokenizer *tokenizer);
void        parse_digits(t_tokenizer *tokenizer);
void        parse_decimal(t_tokenizer *tokenizer);

// Debug functions
void        debug_token(t_token *token, const char *message);

#endif // PARSER_H
