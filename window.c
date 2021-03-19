/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 08:53:50 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/19 19:48:36 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int		key_hook(int keycode, win_data *win)
{
	if (keycode == 53 || keycode == 65307)
	{
		mlx_destroy_image(win->mlx, win->world.img);
		ft_exit(win);
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
	build_view(win);
	return 0;
}

int		ft_exit(win_data *win)
{
	int	y;

	y = 0;
	while (y < win->settings.mapy)
		free(win->settings.map[y++]);
//	free(win->settings.map);
	free(win->settings.north_texture);
	free(win->settings.west_texture);
	free(win->settings.east_texture);
	free(win->settings.south_texture);
	free(win->settings.sprite_texture);
	//if (win == 1)
	mlx_destroy_window(win->mlx, win->win);
	//free(s->mlx.ptr);
	exit(0);
}

void	print_ray(ray_data ray)
{
	printf("-----------------------------------\n");
	printf("-----ray------------------------\n");
	//printf("rayx: %lf\n",ray.horx);
	//printf("rayy: %lf\n",ray.hory);
	//printf("rayx_map: %lf\n",ray.horx/SCALE);
	//printf("rayy_map: %lf\n",ray.hory/SCALE);
	printf("horx: %lf\n",floor(ray.horx));
	printf("hory: %lf\n",floor(ray.hory));
	printf("-----------------------------------\n");
	printf("verx: %lf\n",floor(ray.verx));
	printf("very: %lf\n",floor(ray.very));
	printf("-----------------------------------\n");
	printf("rayx: %lf\n",floor(ray.rayx));
	printf("rayy: %lf\n",floor(ray.rayy));
	//	printf("speed: %d\n",player.speed);
	printf("-----------------------------------\n");
	printf("-----------------------------------\n");
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
