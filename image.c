/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/23 11:43:29 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		build_view(win_data *win)
{
	new_image(win, &win->world);
	new_image(win, &win->view);
	if(!build_world(&win->world, win->settings.map, &win->player))
		return (0);
	view_background(&win->view, &win->settings);

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
	win->ray.angle = win->player.angle + FOV/2;
	int i = 0;
	int x = 0;
	while (i++ < W_IMG)
	{
		win->ray.dirx = cos(win->ray.angle);
		win->ray.diry = -sin(win->ray.angle);
		check_hor_intersection(win,&win->settings, win->player, &win->ray);
		check_ver_intersection(win,&win->settings, win->player, &win->ray);
		set_ray(win->player,&win->ray);
		my_mlx_put_wall(win, &win->view, x, RED);
		win->ray.angle -= FOV/W_IMG;
		x++;
	}
	return (1);
}

void	check_hor_intersection(win_data *win, sett_data *settings, pl_data player, ray_data *ray)
{
	//TOGLIERE WIN DATA WIN , TOGLIERE MY_MLX_PIXEL_PUT
	int		roundy;
	double	horx;
	double	hory;

	if(ray->diry < 0)
	{
		roundy = 0;
		ray->value_y = 1;
	}
	else
	//if (ray->diry > 0)
	{
		roundy = 1;
		ray->value_y = -1;
	}

	hory = floor(player.posy) + roundy;
	horx = player.posx + (fabs((player.posy) -(hory))
				/ (ray->value_y * tan(ray->angle)));
	while (floor(horx) >= 0 && floor(horx) < settings->mapx)
	{
		if (settings->map[(int)floor((hory) + (roundy - 1))][(int)floor(horx)] == '1')
		{
			my_mlx_pixel_put(&win->world, horx*SCALE, hory*SCALE, WHITE);
			ray->horx = horx;
			ray->hory = hory;
			return ;
		}
		my_mlx_pixel_put(&win->world, horx*SCALE, hory*SCALE, WHITE);
		hory -= ray->value_y;
		horx += ray->value_y/tan(ray->angle);
	}
	ray->horx = MY_MAX_LIMIT;
	ray->hory = MY_MAX_LIMIT;
}

void	check_ver_intersection(win_data *win,sett_data *settings, pl_data player, ray_data *ray)
{
	int		roundx;
	double	verx;
	double	very;

	if(ray->dirx < 0)
	{
		roundx = 0;
		ray->value_x = 1;
	}
	//if (ray->dirx > 0)
	else
	{
		roundx = 1;
		ray->value_x = -1;
	}
		verx = floor(player.posx / 1) * 1 + roundx;
		very = player.posy + (fabs(player.posx - verx))
		* (ray->value_x * tan(ray->angle));
		while((floor(very) > 0 && floor(very) < settings->mapy))
		{
			if (settings->map[(int)floor(very)][(int)floor(verx + (roundx - 1) )] == '1')
			{
				my_mlx_pixel_put(&win->world, verx*SCALE, very*SCALE, YELLOW);
				ray->verx = verx;
				ray->very = very;
				return ;
			}
			my_mlx_pixel_put(&win->world, verx*SCALE, very*SCALE, YELLOW);
			verx -= ray->value_x ;
			very += ray->value_x *tan(ray->angle);
		 }
	ray->verx = MY_MAX_LIMIT;
	ray->very = MY_MAX_LIMIT;
}
