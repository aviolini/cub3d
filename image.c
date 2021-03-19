/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/19 11:32:24 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		build_view(win_data *win)
{
	new_image(win, &win->world);
	new_image(win, &win->view);
	if(!build_world(&win->world, win->settings.map, &win->player))
		return (0);
	view_background(&win->view);

	image(win);
	miniray(win);

	mlx_put_image_to_window(win->mlx, win->win, win->world.img, 20, 20);
	mlx_put_image_to_window(win->mlx, win->win, win->view.img, W_IMG + 25, 20);

	mlx_destroy_image(win->mlx, win->world.img);
	mlx_destroy_image(win->mlx, win->view.img);

	return (1);
}

int		image(win_data *win)
{
	check_hor_intersection(win,&win->settings, win->player, &win->ray);
	check_ver_intersection(win,&win->settings, win->player, &win->ray);
	set_ray(win->player,&win->ray);
	print_ray(win->ray);
	return (1);
}

void	miniray(win_data *win)
{
	my_mlx_pixel_put(&win->world, win->player.posx, win->player.posy,0x00ffffff);
	int i = 0;
	double rayy = win->player.posy, rayx = win->player.posx;
	while (i++< 5){
		rayy += win->player.diry;
		rayx += win->player.dirx;
		my_mlx_pixel_put(&win->world, rayx, rayy,0x00ffffff);
	}
}
