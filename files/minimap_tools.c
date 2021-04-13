/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:24:41 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 13:46:32 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_intersection(t_window *win, double intersX, double intersY)
{
	if (win->settings.minimap_def)
		my_mlx_pixel_put(&win->world, intersX * SCALE, intersY * SCALE, RED);
}

void	miniray(t_window *win)
{
	int		i;
	double	rayy;
	double	rayx;

	my_mlx_pixel_put(&win->world, win->player.posX * SCALE, \
									win->player.posY * SCALE, BLACK);
	i = 0;
	rayy = win->player.posY * SCALE;
	rayx = win->player.posX * SCALE;
	while (i++ < 6)
	{
		rayy += win->player.dirY;
		rayx += win->player.dirX;
		my_mlx_pixel_put(&win->world, rayx, rayy, BLACK);
	}
}

void	my_mlx_pixel_wall(t_image *img, int x, int y, int color)
{
	char	*dst;
	int		i;
	int		z;

	i = -1;
	while (++i < SCALE)
	{
		z = -1;
		while (++z < SCALE)
		{
			dst = img->addr + ((i + y) * img->line_length + \
				(x + z) * (img->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
}

void	draw_grid_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + ((y) * img->line_length + \
						(x) * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
