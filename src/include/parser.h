/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:22:49 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/14 15:42:11 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// to prevent cross includes
# include "objects.h"
# include <stdbool.h>
# include <stddef.h>

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
}	t_tokenizer;

// Define the parser
typedef struct s_parser {
    t_tokenizer *tokenizer;
} t_parser;

// Create a new parser
t_parser    *parser_new(t_tokenizer *tokenizer);

// Parse the stream of tokens and return the AST
t_scene     *parser_parse(t_parser *parser);


// Free the parser
void        parser_free(t_parser *parser);
void        token_free(t_token *token);
t_v3        parse_v3(t_parser *parser);


// needs to be organized, just to test for now:






// Create a new tokenizer
t_tokenizer	*tokenizer_new(char *input);

// Get the next token from the tokenizer
t_token		*tokenizer_next(t_tokenizer *tokenizer);

// Free the tokenizer
void		tokenizer_free(t_tokenizer *tokenizer);

// needs to be organized, just to test for now:
char		*parse_keyword(t_tokenizer *tokenizer);
char		*parse_identifier(t_tokenizer *tokenizer);
char		*parse_symbol(t_tokenizer *tokenizer);
double		parse_number(t_tokenizer *tokenizer);
t_amb_light *parse_ambient_light(t_parser *parser);
t_camera    *parse_camera(t_parser *parser);
t_light     *parse_light(t_parser *parser);
t_sphere    *parse_sphere(t_parser *parser);
t_plane     *parse_plane(t_parser *parser);
t_cylinder  *parse_cylinder(t_parser *parser);
t_colr      parse_color(t_parser *parser);

bool	ft_isspace(char c);


#endif // PARSER_H