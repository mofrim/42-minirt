/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:09:25 by fmaurer           #+#    #+#             */
/*   Updated: 2025/05/26 20:15:06 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <float.h>

# ifdef RUBI
#  define WINX 				1200
#  define WINY 				700
/* The Area reserved for the sidebar. */
#  define PIXEL_MINX 		-466
#  define PIXEL_MAXX 		466
#  define PIXEL_MINY 		-350
#  define PIXEL_MAXY 		350
// # define CANVAS_WIDTH		(WINX - SIDEBAR_AREA_X)
#  define CANVAS_WIDTH		932
// # define CANVAS_OFFSET_X	(CANVAS_MINX + CANVAS_WIDTH/2)
#  define CANVAS_OFFSET_X	734
// # define CANVAS_OFFSET_Y	(WINY/2)
#  define CANVAS_OFFSET_Y	350
#  define SIDEBAR_AREA_X	268
#  define FONT_BIG "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
#  define FONT_DEFAULT "-misc-fixed-*-*-*-*-13-*-*-*-*-*-*-*"
// # define FONT "-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso8859-1"
// # define FONT "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-1"
# endif

# ifdef DEFAULT
#  define WINX 					1600
#  define WINY 					1000
/* The Area reserved for the sidebar. */
#  define PIXEL_MINX 			-666
#  define PIXEL_MAXX 			666
#  define PIXEL_MINY 			-500
#  define PIXEL_MAXY 			500
// # define CANVAS_WIDTH		(WINX - CANVAS_MINX)
#  define CANVAS_WIDTH			1332
// # define CANVAS_OFFSET_X		(SIDEBAR_AREA_X + CANVAS_WIDTH/2)
#  define CANVAS_OFFSET_X		934
// # define CANVAS_OFFSET_Y		(WINY/2)
#  define CANVAS_OFFSET_Y		500
#  define SIDEBAR_AREA_X		268
#  define FONT_BIG "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
#  define FONT_DEFAULT "-misc-fixed-*-*-*-*-15-*-*-*-*-*-*-*"
// # define FONT "-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso8859-1"
// # define FONT "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-1"
# endif

# ifdef SCHOOL
#  define WINX 					2400
#  define WINY 					1500
/* The Area reserved for the sidebar. */
#  define PIXEL_MINX 			-1066
#  define PIXEL_MAXX 			1066
#  define PIXEL_MINY 			-750
#  define PIXEL_MAXY 			750
// # define CANVAS_WIDTH		(WINX - CANVAS_MINX)
#  define CANVAS_WIDTH			2132
// # define CANVAS_OFFSET_X		(CANVAS_MINX + CANVAS_WIDTH/2)
#  define CANVAS_OFFSET_X		1334
// # define CANVAS_OFFSET_Y		(WINY/2)
#  define CANVAS_OFFSET_Y		750
#  define SIDEBAR_AREA_X		268
#  define FONT_BIG "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
#  define FONT_DEFAULT "-misc-fixed-*-*-*-*-15-*-*-*-*-*-*-*"
// # define FONT "-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso8859-1"
// # define FONT "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-1"
# endif

/* Infinity. Kind of. For now.... */
# define INF	10000.0

/* For now our viewport is fixed at EPS from camera. */
# define VIEWZ	EPS

/* Read buffer size for reading scene file. */
# define FILE_BUFSIZE 1000

/* Well this is our precision / threshold for use in comparisons because
 * double precision floating point calculations never exactly give you the value
 * you might ask for in a statement like
 * 		if (x == 42)
 * 			...
 * With EPS this statement becomes
 * 		if (fabs(x - 42) <= EPS)
 * 			...
 */
# define EPS 1e-12f

/* Bonus mutlithread business... */
# ifndef BONUS
#  define BONUS 0
# endif
# ifndef THREADS
#  define THREADS 1
# endif

#endif
