/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:52:15 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/04 11:26:00 by zrz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	parse_number(t_tokenizer *tokenizer)
{
	t_token	*token;
	double	value;

	token = parse_number_token(tokenizer);
	if (!token)
		return (0.0);
	value = token->u_value.num;
	token_free(token);
	return (value);
}


// function to validate color components
bool validate_color_components(char **parts, bool *valid)
{
    int r, g, b;
    
    // Check if we have exactly 3 parts
    if (!parts[0] || !parts[1] || !parts[2] || parts[3])
    {
        ft_putendl_fd("Error: Color must have exactly 3 components", 2);
        *valid = false;
        return (false);
    }
    
    // Check if all parts are numeric
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; parts[i][j]; j++)
        {
            if (!ft_isdigit(parts[i][j]))
            {
                ft_putendl_fd("Error: Color components must be numeric", 2);
                *valid = false;
                return (false);
            }
        }
    }
    
    // Convert and validate range
    r = ft_atoi(parts[0]);
    g = ft_atoi(parts[1]);
    b = ft_atoi(parts[2]);
    
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        ft_putendl_fd("Error: Color components must be between 0 and 255", 2);
        *valid = false;
        return (false);
    }
    
    return (true);
}

bool validate_vector_components(char **parts, bool *valid)
{
    // Check if we have exactly 3 parts
    if (!parts[0] || !parts[1] || !parts[2] || parts[3])
    {
        ft_putendl_fd("Error: Vector must have exactly 3 components", 2);
        *valid = false;
        return (false);
    }
    
    // Check if all parts are valid floating point numbers
    for (int i = 0; i < 3; i++)
    {
        int j = 0;
        
        // Skip sign
        if (parts[i][j] == '-' || parts[i][j] == '+')
            j++;
        
        // Must have at least one digit
        if (!ft_isdigit(parts[i][j]))
        {
            ft_putendl_fd("Error: Vector components must be numeric", 2);
            *valid = false;
            return (false);
        }
        
        // Check digits before decimal
        while (ft_isdigit(parts[i][j]))
            j++;
        
        // Check decimal part if present
        if (parts[i][j] == '.')
        {
            j++;
            // Must have at least one digit after decimal
            if (!ft_isdigit(parts[i][j]))
            {
                ft_putendl_fd("Error: Invalid floating point format", 2);
                *valid = false;
                return (false);
            }
            while (ft_isdigit(parts[i][j]))
                j++;
        }
        
        // No other characters allowed
        if (parts[i][j] != '\0')
        {
            ft_putendl_fd("Error: Invalid character in vector component", 2);
            *valid = false;
            return (false);
        }
    }
    
    return (true);
}