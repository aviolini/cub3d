/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/29 10:35:20 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		build_view(t_window *win)
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

int		image(t_window *win)
{
	win->ray.angle = win->player.angle + FOV/2;
	int i = 0;
	int x = 0;
	//int color;
	int orientation;
	while (i++ < W_IMG)
	{
		win->ray.dirX = cos(win->ray.angle);
		win->ray.dirY = -sin(win->ray.angle);
		check_hor_intersection(win,&win->settings, win->player, &win->ray);
		check_ver_intersection(win,&win->settings, win->player, &win->ray);
		orientation = set_distance_and_wall_orientation(win->player,&win->ray);
	//	color = set_wall_color(orientation);
	//	my_mlx_put_wall(win, &win->view, x, color);
		column(win, &win->view,x,orientation);
		win->ray.angle -= FOV/W_IMG;
		x++;
	}
	return (1);
}

void	check_hor_intersection(t_window *win, t_settings *settings, t_player player, t_ray *ray)
{
	//TOGLIERE WIN DATA WIN , TOGLIERE MY_MLX_PIXEL_PUT
	int		roundy;
	double	horx;
	double	hory;

	if(ray->dirY < 0)
	{
		roundy = 0;
		ray->value_y = 1;
	}
	else
	//if (ray->dirY > 0)
	{
		roundy = 1;
		ray->value_y = -1;
	}

	hory = floor(player.posY) + roundy;
	horx = player.posX + (fabs((player.posY) -(hory))
				/ (ray->value_y * tan(ray->angle)));
	while (floor(horx) >= 0 && floor(horx) < settings->mapW)
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

void	check_ver_intersection(t_window *win,t_settings *settings, t_player player, t_ray *ray)
{
	int		roundx;
	double	verx;
	double	very;

	if(ray->dirX < 0)
	{
		roundx = 0;
		ray->value_x = 1;
	}
	//if (ray->dirX > 0)
	else
	{
		roundx = 1;
		ray->value_x = -1;
	}
		verx = floor(player.posX / 1) * 1 + roundx;
		very = player.posY + (fabs(player.posX - verx))
		* (ray->value_x * tan(ray->angle));
		while((floor(very) > 0 && floor(very) < settings->mapH))
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
