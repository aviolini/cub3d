/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 08:53:50 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/16 11:38:31 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main_window(win_data *win)
{
	win->mlx = mlx_init();
	set_right_resolution(win);
	win->win = mlx_new_window(win->mlx,win->settings.win_resx,
		win->settings.win_resy, "Welcome");
	new_image(win, &win->world);
	if(!build_world(&win->world, win->settings.map, &win->player))
		return (0);
	bundle_ray(win);
	mlx_put_image_to_window(win->mlx, win->win, win->world.img, 20, 20);
	print_player(win->player);
	mlx_hook(win->win, 2, 1L<<0, key_hook, win);
	mlx_loop(win->mlx);
	return (1);
}

int		key_hook(int keycode, win_data *win)
{
	mlx_destroy_image(win->mlx, win->world.img);
	new_image(win, &win->world);
//	if(!build_world(&win->world, win->settings.map, &win->player))
//		return (0);
	if (keycode == 53 || keycode == 65307)
	{
		mlx_destroy_image(win->mlx, win->world.img);
		//DESTROY WINDOW
		exit(0);
	}
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
	bundle_ray(win);
	mlx_put_image_to_window(win->mlx, win->win, win->world.img, 20, 20);
	return 0;
}

void	print_player(pl_data player)
{
	printf("-----player------------------------\n");
	printf("posx: %lf\n",player.posx);
	printf("posy: %lf\n",player.posy);
	printf("posx_map: %lf\n",player.posx/SCALE);
	printf("posy_map: %lf\n",player.posy/SCALE);
	printf("dirx: %lf\n",player.dirx);
	printf("diry: %lf\n",player.diry);
	printf("speed: %d\n",player.speed);
	printf("-----------------------------------\n");
}
