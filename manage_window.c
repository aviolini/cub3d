/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 08:53:50 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/15 18:11:27 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main_window(win_data *win)
{
	win->mlx = mlx_init();
	//set_right_resolution(win);
	win->win = mlx_new_window(win->mlx,win->settings.win_resx,
		win->settings.win_resy, "Welcome");
	new_image(win, &win->world);
	if(!build_world(&win->world, win->settings.map, &win->player))
		return (0);
	//mlx_put_image_to_window(win->mlx, win->win, win->world.img, 20, 20);
	print_player(win->player);
	mlx_hook(win->win, 2, 1L<<0, key_hook, win);
	mlx_loop(win->mlx);
	return (1);
}

int		key_hook(int keycode, win_data *win)
{
	if (keycode == 53 || keycode == 65307)
	{
		mlx_destroy_image(win->mlx, win->world.img);
		//DESTROY WINDOW
		exit(0);
	}
	if(keycode == 126 || keycode == 65362 || keycode == 119)//W
	{
		mlx_destroy_image(win->mlx, win->world.img);
		new_image(win, &win->world);
		if(!build_world(&win->world, win->settings.map, &win->player))
			return (0);
		win->player.posy += win->player.diry;
		win->player.posx += win->player.dirx;
	}
	if(keycode == 125 || keycode == 65364 || keycode == 115)//S
	{
		mlx_destroy_image(win->mlx, win->world.img);
		new_image(win, &win->world);
		if(!build_world(&win->world, win->settings.map, &win->player))
			return (0);
		win->player.posy -= win->player.diry;
		win->player.posx -= win->player.dirx;
	}
	if(keycode == 2 || keycode == 100)//D
	{
		mlx_destroy_image(win->mlx, win->world.img);
		new_image(win, &win->world);
		if(!build_world(&win->world, win->settings.map, &win->player))
			return (0);
		win->player.posy -= win->player.dirx;
		win->player.posx -= win->player.diry;
	}
	if (keycode == 0 || keycode == 97)//A
	{
		mlx_destroy_image(win->mlx, win->world.img);
		new_image(win, &win->world);
		if(!build_world(&win->world, win->settings.map, &win->player))
			return (0);
		win->player.posy -= win->player.dirx;
		win->player.posx += win->player.diry;
	}
	if(keycode == 124 || keycode == 65363) //RIGHT
	{
		mlx_destroy_image(win->mlx, win->world.img);
		new_image(win, &win->world);
		if(!build_world(&win->world, win->settings.map, &win->player))
			return (0);
		win->player.angle -= M_PI/12;
		win->player.dirx = cos(win->player.angle);
		win->player.diry = -sin(win->player.angle);
	}
	if(keycode == 123 || keycode == 65361) //LEFT
	{
		mlx_destroy_image(win->mlx, win->world.img);
		new_image(win, &win->world);
		if(!build_world(&win->world, win->settings.map, &win->player))
			return (0);
		win->player.angle += M_PI/12;
		win->player.dirx = cos(win->player.angle);
		win->player.diry = -sin(win->player.angle);
	}
	int i = 0;
	double rayx,rayy;
	rayx = win->player.posx;
	rayy = win->player.posy;
	while (i++ < 10){
		rayx += win->player.dirx;
		rayy += win->player.diry;
		my_mlx_pixel_put(&win->world, rayx, rayy,0x00ffffff);
	}
	mlx_put_image_to_window(win->mlx, win->win, win->world.img, 20, 20);
	return 0;
}

void	print_player(pl_data player)
{
	printf("-----player------------------------\n");
	printf("posx: %lf\n",player.posx);
	printf("posy: %lf\n",player.posy);
	printf("dirx: %lf\n",player.dirx);
	printf("diry: %lf\n",player.diry);
	printf("speed: %d\n",player.speed);
	printf("-----------------------------------\n");
}
