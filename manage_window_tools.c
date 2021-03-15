/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:13:56 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/15 19:08:07 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		build_world(img_data *world, char **map, pl_data *player)
{
	int y;
	int x;
	//int def;

	y = -1;
	x = -1;
	//def = 0;	//RIMETTERLO INSIEME A RETURN=0 (RIGA 35) PER IL CONTROLLO
				//DEI DOPPI CARATTERI
				//SE SI LASCIA PLAYER->DEF INIZIALIZZARLO
				//LA STRUTTURA PLAYER NON E' STATA INIZIALIZZATA
	while(map[++y] && -2 < (x = -1))
	{
		while(map[y][++x])
		{
			if (map[y][x] == '1')
				my_mlx_pixel_wall(world, x * SCALE, y * SCALE,0x000000ff);
			else if(map[y][x] == '2')
				my_mlx_pixel_put(world, x * SCALE, y * SCALE,0x00ff0000);
			else if(map[y][x] == '0')
				my_mlx_pixel_grid(world, x * SCALE, y * SCALE,0x00ff0000);
			else if(map[y][x] != ' ' && map[y][x] != '0')
			{
				if (player->def != 1)
				{
				//	return (0);
				build_player(map, x, y, player);
				my_mlx_pixel_put(world, player->posx, player->posy,0x00ffffff);
				player->def = 1;
			}
			}
		}
	}
	return (1);
}

void	build_player(char **map,int x, int y, pl_data *player)
{
	player->speed = 1;
	player->posx = x * SCALE;// + SCALE / 2;
	player->posy = y * SCALE;// + SCALE / 2;
	if (map[y][x] == 'N')
		player->angle = M_PI_2;
	else if (map[y][x] == 'S')
		player->angle = 3*M_PI_2;
	else if (map[y][x] == 'E')
		player->angle = 0;
	else if (map[y][x] == 'W')
		player->angle = M_PI;
	player->dirx = cos(player->angle);
	player->diry = -sin(player->angle);
}

void	set_right_resolution(win_data *win)
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
