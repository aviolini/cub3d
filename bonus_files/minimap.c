/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:59:02 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 13:46:46 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	new_minimap_image(t_window *win, t_image *image)
{
	image->img = mlx_new_image(win->mlx, win->settings.mapW * SCALE, \
		 						win->settings.mapH * SCALE);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, \
								&image->line_length, &image->endian);
}

int	build_world(t_image *world, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '1' || map[y][x] == 'N' || map[y][x] == 'S' || \
										map[y][x] == 'E' || map[y][x] == 'W')
				my_mlx_pixel_wall(world, x * SCALE, y * SCALE, GRAY);
			if (map[y][x] == '2')
			{
				my_mlx_pixel_put(world, x * SCALE + SCALE / 2 - 1, y * \
											SCALE + SCALE / 2 - 1, YELLOW);
				my_mlx_pixel_put(world, x * SCALE + SCALE / 2, y * \
											SCALE + SCALE / 2, YELLOW);
				my_mlx_pixel_put(world, x * SCALE + SCALE / 2, y * \
											SCALE + SCALE / 2 - 1, YELLOW);
				my_mlx_pixel_put(world, x * SCALE + SCALE / 2 - 1, y * \
											SCALE + SCALE / 2, YELLOW);
			}
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' || \
										map[y][x] == 'E' || map[y][x] == 'W')
				my_mlx_pixel_grid(world, x * SCALE, y * SCALE);
		}
	}
	return (1);
}

void	my_mlx_pixel_grid(t_image *img, int x, int y)
{
	int		i;
	int		z;

	i = -1;
	while (++i <= SCALE)
	{
		z = -1;
		if (i == 0 || i == SCALE)
		{
			while (++z < SCALE)
				draw_grid_pixel(img, x + z, i + y, GRAY);
		}
		else
		{
			while (++z <= SCALE)
			{
				if (z == 0 || z == SCALE)
					draw_grid_pixel(img, x + z, i + y, GRAY);
				else
					draw_grid_pixel(img, x + z, i + y, WHITE);
			}
		}
	}
}
