/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:22:49 by jroseiro          #+#    #+#             */
/*   Updated: 2025/05/22 14:37:38 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// to prevent cross includes
# include "objects.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

/* Forward declarations from minirt.h */
typedef struct s_scene	t_scene;
typedef struct s_mrt	t_mrt;

// Define the different types of tokens
typedef enum e_tokentype
{
	TOKEN_TYPE_KEYWORD,
	TOKEN_TYPE_V3,
	TOKEN_TYPE_COLR,
	TOKEN_TYPE_NUM,
	TOKEN_TYPE_NULL
}	t_tokentype;

// Define the structure of a token
typedef struct s_token
{
	t_tokentype	type;
	union
	{
		char	*str;
		double	num;
	}	u_value;
}	t_token;

/* The "tokenizer". Also used for carrying along the valid flag which will get
 * set to false if any parsing func encounters an error. */
typedef struct s_tokenizer
{
	char	*input;
	size_t	pos;
	size_t	len;
	bool	valid;
}	t_tokenizer;

/********** PARSER FUNCTIONS **********/

// Main parsing functions
int			get_scene_from_parser(t_tokenizer *tokenizer, t_scene *scene);
t_scene		*parse_scene(char *scene_filename, t_mrt *mrt);
t_scene		*init_scene(void);
int			lineparse_scenefile(char *file_content, t_scene *scene);
void		handle_token_keyword(t_scene *scene, t_tokenizer *tokenizer,
				char *key);

// Object parsers
t_alight	*parse_ambient_light(t_tokenizer *tokenizer);
t_camera	*parse_camera(t_tokenizer *tokenizer);
t_light		*parse_light(t_tokenizer *tokenizer);
t_colr		parse_color(t_tokenizer *tokenizer);
t_sphere	*parse_sphere(t_tokenizer *tokenizer);
t_plane		*parse_plane(t_tokenizer *tokenizer);
t_cylinder	*parse_cylinder(t_tokenizer *tokenizer);
t_triangle	*parse_triangle(t_tokenizer *tokenizer);
t_circle	*parse_circle(t_tokenizer *tokenizer);
t_hyper		*parse_hyper(t_tokenizer *tok);

// Parser utilities
t_v3		parse_v3(t_tokenizer *tok);
t_v3		parse_v3_from_parts(char **parts);
float		parse_pos_num(t_tokenizer *tok);
float		parse_pos_num_maybe(t_tokenizer *tok);
char		*read_scenefile(char *filename);
bool		has_rt_ext(char *filename);
bool		validate_color(char **parts, bool *valid);
bool		validate_vector(char **parts, bool *valid);
char		*get_tokstr(t_tokenizer *tok);

/********** TOKENIZER FUNCTIONS **********/

t_tokenizer	*tokenizer_new(char *input);
t_token		*get_next_token(t_tokenizer *tokenizer);
void		token_free(t_token **token);
t_token		*get_null_token(void);

// Token type parsers
t_token		*parse_coordinate(t_tokenizer *tokenizer);
t_token		*parse_keyword(t_tokenizer *tokenizer);
t_token		*parse_number_token(t_tokenizer *tokenizer);
char		*parse_texture_maybe(t_tokenizer *tok);
char		*parse_nmap_maybe(t_tokenizer *tok);
bool		parse_bump_maybe(t_tokenizer *tok);
bool		parse_checker_maybe(t_tokenizer *tok);
int			parse_hyperchecker_maybe(t_tokenizer *tok);

// Helper functions for tokenizing
void		skip_whitespace(t_tokenizer *tokenizer);
int			is_coordinate(t_tokenizer *tokenizer);
void		skip_sign(t_tokenizer *tokenizer);
void		parse_digits(t_tokenizer *tokenizer);
void		parse_decimal(t_tokenizer *tokenizer);

// Debug functions
void		debug_token(t_token *token, const char *message);

#endif
