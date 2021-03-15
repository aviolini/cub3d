/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:13:56 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/15 12:39:14 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_right_resolution(win_data *win)
{
	(void)win;
/*	int myresx;
	int myresy;
	mlx_get_screen_size(win->mlx, &myresx, &myresy);
	if(win->settings.win_resx > myresx)
		win->settings.win_resx = myresx;
	if(win->settings.win_resy > myresy)
		win->settings.win_resy = myresy;
*/}

void	my_mlx_pixel_put(img_data *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	my_mlx_pixel_put2(img_data *img, int x, int y, int color)
{
    char    *dst;
	int		i = -1, z = -1;

	while (++i <= SCALE && -2 < (z = -1))
		while (++z <= SCALE)
		{
    		dst = img->addr + ((i + y) * img->line_length +
			(x + z) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
		}
}

int		build_world(img_data *world, char **map, pl_data *player)
{
	int y;
	int x;
	int def;

	y = -1;
	x = -1;
	def = 0;
	while(map[++y] && -2 < (x = -1))
	{
	//	printf("map[y] : %s\n",map[y]);
		while(map[y][++x])
		{
			if (map[y][x] == '1')
				my_mlx_pixel_put2(world, x * SCALE, y * SCALE, 0x00FFFFFF);
			else if(map[y][x] == '2')
				my_mlx_pixel_put2(world, x * SCALE, y * SCALE, 0x0000FFFF);
			else if(map[y][x] != ' ' && map[y][x] != '0')
			{
				if (def == 0)
				{
					build_player(map, x, y, player);
					my_mlx_pixel_put2(world, x * SCALE, y * SCALE, 0x00FFFF00);
					def = 1;
				}
				else
					return (0);
			}
		}
	}
	return (1);
}

void	build_player(char **map,int x, int y, pl_data *player)
{
	player->speed = 1;
	player->posx = x;
	player->posy = y;
	if (map[y][x] == 'N')
		player->angle = M_PI_2;
	else if (map[y][x] == 'S')
		player->angle = 3 * M_PI_2;
	else if (map[y][x] == 'E')
		player->angle = 0;
	else if (map[y][x] == 'W')
		player->angle = M_PI;
}
