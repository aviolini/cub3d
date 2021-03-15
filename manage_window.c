/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 08:53:50 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/15 12:38:30 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main_window(win_data *win)
{
	//init_player(&win->player);
	//print_player(win->player);
	win->mlx = mlx_init();
	//set_right_resolution(win);
	win->win = mlx_new_window(win->mlx,win->settings.win_resx,
		win->settings.win_resy, "Welcome");
	//CREATE WORLD IMAGE
	win->world.img = mlx_new_image(win->mlx, W_IMG, H_IMG);
	win->world.addr = mlx_get_data_addr(win->world.img, &win->world.bits_per_pixel,
		&win->world.line_length, &win->world.endian);
	if(!build_world(&win->world, win->settings.map, &win->player))
		return (0);
	mlx_put_image_to_window(win->mlx, win->win, win->world.img, 20, 20);
	//
	//mlx_hook(win->win, 2, 1L<<0, key_hook, &win);
	print_player(win->player);
	mlx_loop(win->mlx);
	return (1);
}

void	init_player(pl_data *player)
{
	player->posx = -1;
	player->posy = -1;
	player->dirx = 0;
	player->diry = 0;
	player->angle = -1;
	player->speed = 1;
}

void	print_player(pl_data player)
{
	printf("-----player------------------------\n");
	printf("posx: %lf\n",player.posx);
	printf("posy: %lf\n",player.posy);
	printf("dirx: %lf\n",player.dirx);
	printf("diry: %lf\n",player.diry);
	printf("angle: %lf\n",player.angle);
	printf("speed: %d\n",player.speed);
	printf("-----------------------------------\n");
}
