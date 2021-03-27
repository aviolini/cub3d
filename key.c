/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 08:53:50 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/27 09:07:29 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_hook(int keycode,t_window *win)
{
	if (keycode == 53 || keycode == 65307)
		ft_exit(win);
	if(keycode == 126 || keycode == 65362 || keycode == 119)//W
		move(win->settings.map, &win->player,'w');
	if(keycode == 125 || keycode == 65364 || keycode == 115)//S
		move(win->settings.map, &win->player,'s');
	if(keycode == 2 || keycode == 100)//D
		slide(win->settings.map, &win->player,'d');
	if (keycode == 0 || keycode == 97)//A
		slide(win->settings.map, &win->player,'a');
	if(keycode == 124 || keycode == 65363) //RIGHT
		rotate(&win->player,'r');
	if(keycode == 123 || keycode == 65361) //LEFT
		rotate(&win->player,'l');
	build_view(win);
	return 0;
}

void	move(char **map, t_player *player, char var)
{
	int		value;
	if (var == 'w')
		value = 1;
	if (var == 's')
		value = -1;
	player->posy += (value)*player->diry * SPEED/SCALE;
	player->posx += (value)*player->dirx * SPEED/SCALE;
	while(map[(int)floor(player->posy)]
		[(int)floor(player->posx)] == '1')
	{
		player->posy -= (value)*player->diry/SCALE;
		player->posx -= (value)*player->dirx/SCALE;
	}
}

void	slide(char **map, t_player *player, char var)
{
	int		value;
	if (var == 'a')
		value = -1;
	if (var == 'd')
		value = 1;
	player->posy += (value) * player->dirx * SPEED/SCALE;
	player->posx -= (value) * player->diry * SPEED/SCALE;
	while(map[(int)floor(player->posy)]
		[(int)floor(player->posx)] == '1')
	{
		player->posy -= (value) * player->dirx/SCALE;
		player->posx += (value) * player->diry/SCALE;
	}
}

void	rotate(t_player *player, char var)
{
	int		value;
	if (var == 'r')
		value = -1;
	if (var == 'l')
		value = 1;
	if (player->angle + (value) * ROTATION > 2 * M_PI)
		player->angle = (value) * ROTATION;
	else if (player->angle + (value) * ROTATION < 0)
		player->angle = 2 * M_PI + (value) * ROTATION;
	else
		player->angle += (value) * ROTATION;
	player->dirx = cos(player->angle);
	player->diry = -sin(player->angle);
}

int		ft_exit(t_window *win)
{
	int	y;
	y = 0;
	while (y < win->settings.mapy)
		free(win->settings.map[y++]);
	free(win->settings.map);
	free(win->settings.north_texture);
	free(win->settings.west_texture);
	free(win->settings.east_texture);
	free(win->settings.south_texture);
	free(win->settings.sprite_texture);
	if (win->settings.win_def == 1)
		mlx_destroy_window(win->mlx, win->win);
	exit(0);
}
