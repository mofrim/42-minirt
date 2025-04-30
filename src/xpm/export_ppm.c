/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ppm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:08:59 by fmaurer           #+#    #+#             */
/*   Updated: 2025/04/30 13:29:58 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_intcolr_from_data(unsigned char *addr, int opp);
static void	print_pxcolr_triplet(int fd, unsigned char *dat, int opp);

/**
 * Export the current scene to `scene.ppm` in the current dir.
 *
 * Quick and dirty but it works. `scene.ppm` will be overwritten without
 * asking! PPM tunred out to be the easiest image format.
 */
int	export_ppm(t_xpm_canvas xc)
{
	int		fd;
	int		x;
	int		y;

	fd = open("./scene.ppm", O_RDWR | O_CREAT | O_TRUNC, 0660);
	if (fd == -1)
		return (printf("can't create/open scene.ppm\n"), -1);
	ft_dprintf(fd, "P3\n%d %d\n255\n", CANVAS_WIDTH, WINY);
	y = -1;
	while (++y < WINY)
	{
		x = -1;
		while (++x < CANVAS_WIDTH)
		{
			print_pxcolr_triplet(fd,
				&xc.data[y * xc.xpm_line_len + x * xc.opp], xc.opp);
			if (x != CANVAS_WIDTH - 1)
				ft_dprintf(fd, "\t");
		}
		if (!(y % 20))
			ft_printf(".");
		ft_dprintf(fd, "\n");
	}
	return (close(fd), 0);
}

/* Get the color value as an int saved in the char data array. Using the same
 * hack as in the put_pixel_xpm func. Treating the 32bit integer as an usigned
 * char array so we can access the 4 bytes seperately. The highest significant
 * byte won't be touched. */
static int	get_intcolr_from_data(unsigned char *addr, int opp)
{
	int	ret;

	ret = 0;
	while (opp--)
		((unsigned char *)(&ret))[opp] = *(addr + opp);
	return (ret);
}

/* Quick and dirty color printing function for use in export func. */
static void	print_pxcolr_triplet(int fd, unsigned char *dat, int opp)
{
	char	*cr;
	char	*cg;
	char	*cb;
	t_colr	tc;

	tc = int_to_tcolr(get_intcolr_from_data(dat, opp));
	cr = ft_itoa(tc.r);
	cg = ft_itoa(tc.g);
	cb = ft_itoa(tc.b);
	ft_dprintf(fd, "%s %s %s", cr, cg, cb);
	free(cr);
	free(cg);
	free(cb);
}
