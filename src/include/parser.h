/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:22:49 by jroseiro          #+#    #+#             */
/*   Updated: 2025/04/08 10:40:04 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// to prevent cross includes
# include "objects.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

typedef struct s_scene t_scene;

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
	int		position;
	size_t	len;
}	t_tokenizer;

// Define the parser
typedef struct s_parser {
	t_tokenizer *tokenizer;
}	t_parser;

/********** PARSER FUNCTIONS **********/

// Parser initialization and cleanup
t_parser    *parser_new(t_tokenizer *tokenizer);

// Main parsing functions
t_scene     *parser_parse(t_parser *parser);
t_scene     *init_scene(void);
void        parse_tokens_recursive(t_parser *parser, t_scene *scene, bool *valid);

// Token handlers
void        handle_token_keyword(t_parser *parser, t_scene *scene, t_token *token);
void        handle_more_keywords(t_parser *parser, t_scene *scene, t_token *token);

// Object parsers
t_amb_light *parse_ambient_light(t_parser *parser);
t_camera    *parse_camera(t_parser *parser);
t_light     *parse_light(t_parser *parser);
t_colr      parse_color(t_parser *parser, bool *valid);
t_sphere    *parse_sphere(t_parser *parser);
t_plane     *parse_plane(t_parser *parser);
t_cylinder  *parse_cylinder(t_parser *parser);
t_triangle	*parse_triangle(t_parser *parser);
t_circle	*parse_circle(t_parser *parser);

// Parser utilities
t_v3        parse_v3(t_parser *parser, bool *valid);
t_v3        parse_default_v3(void);
t_v3        parse_v3_from_parts(char **parts);
double      parse_number(t_tokenizer *tokenizer);
void        free_parts(char **parts);
void        free_parts_helper(char **parts);
t_colr      validate_color(t_colr color, bool *valid);
char        *validate_file_content(char *filename);
bool        is_rt(char *filename);
bool        validate_color_components(char **parts, bool *valid);
bool        validate_vector_components(char **parts, bool *valid);
bool        has_minimum_required_elements(char *content);

/********** TOKENIZER FUNCTIONS **********/

// Tokenizer initialization and cleanup
t_tokenizer *tokenizer_new(char *input);
void        tokenizer_free(t_tokenizer *tokenizer);

// Token generation
t_token     *tokenizer_next(t_tokenizer *tokenizer);
void        token_free(t_token *token);

// Token type parsers
t_token     *parse_coordinate(t_tokenizer *tokenizer);
t_token     *parse_identifier(t_tokenizer *tokenizer);
t_token     *parse_number_token(t_tokenizer *tokenizer);
t_token     *parse_symbol_token(t_tokenizer *tokenizer);
char        *parse_keyword(t_tokenizer *tokenizer);

// Helper functions for tokenizing
void        skip_whitespace(t_tokenizer *tokenizer);
int         is_coordinate(t_tokenizer *tokenizer);
int         is_identifier(t_tokenizer *tokenizer);
int         is_numeric(t_tokenizer *tokenizer);
void        skip_sign(t_tokenizer *tokenizer);
void        parse_digits(t_tokenizer *tokenizer);
void        parse_decimal(t_tokenizer *tokenizer);
// bool        check_newline(t_tokenizer *tokenizer);

// Debug functions
void        debug_token(t_token *token, const char *message);

#endif // PARSER_H
