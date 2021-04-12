/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/12 18:05:18 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	build_view(t_window *win)
{
	new_minimap_image(win, &win->world);
	if(win->settings.minimap_def)
		if(!build_world(&win->world, win->settings.map, &win->player))
			return (0);
	view_background(&win->view, &win->settings);
	image(win);
	if(win->settings.minimap_def)
	miniray(win);
	sprite(win);
	free(win->ray.distance);
	if (win->settings.save == 0)
	{
		mlx_put_image_to_window(win->mlx, win->win, win->view.img, 05, 0);
		if(win->settings.minimap_def)
			mlx_put_image_to_window(win->mlx, win->win, win->world.img, 20, 20);
		mlx_do_sync(win->mlx);
		mlx_destroy_image(win->mlx, win->world.img);
	}
	else
		ft_bitmap(win);
	return (1);
}

int	image(t_window *win)
{
	unsigned int	i;
	int				orientation;

	i = 0;
	win->ray.angle = win->player.angle + FOV/2;
	win->ray.distance = (double *)malloc(sizeof(double) * win->settings.winW);
	while (i < win->settings.winW)
	{
		win->ray.dirX = cos(win->ray.angle);
		win->ray.dirY = -sin(win->ray.angle);
		check_hor_inters(&win->settings, win->player, &win->ray);
		check_ver_inters(&win->settings, win->player, &win->ray);
		orientation = set_distance_and_wall_orientation(win,win->player,&win->ray,i);
		column(win, &win->view,i,orientation);
		win->ray.angle -= FOV / win->settings.winW;
		i++;
	}
	return (1);
}

void	check_hor_inters(t_settings *settings, t_player player, t_ray *ray)
{
	int		roundy;
	double	horX;
	double	horY;

	if(ray->dirY < 0)
	{
		roundy = 0;
		ray->value = 1;
	}
	else
	{
		roundy = 1;
		ray->value = -1;
	}

	horY = floor(player.posY) + roundy;
	horX = player.posX + (fabs((player.posY) -(horY))
				/ (ray->value * tan(ray->angle)));
	while (floor(horX) >= 0 && floor(horX) < settings->mapW &&
			(settings->map[(int)floor(horY)][(int)floor(horX)] != ' '))
	{

		if (settings->map[(int)floor((horY) + (roundy - 1))][(int)floor(horX)] == '1')
		{
			ray->horX = horX;
			ray->horY = horY;
			return ;
		}
		horY -= ray->value;
		horX += ray->value/tan(ray->angle);
	}
	ray->horX = MY_MAX_LIMIT;
	ray->horY = MY_MAX_LIMIT;
}

void	check_ver_inters(t_settings *settings, t_player player, t_ray *ray)
{
	int		roundx;
	double	verX;
	double	verY;

	if(ray->dirX < 0)
	{
		roundx = 0;
		ray->value = 1;
	}
	else
	{
		roundx = 1;
		ray->value = -1;
	}
		verX = floor(player.posX / 1) * 1 + roundx;
		verY = player.posY + (fabs(player.posX - verX))
		* (ray->value * tan(ray->angle));
		while((floor(verY) >= 0 && floor(verY) < settings->mapH) &&
				(settings->map[(int)floor(verY)][(int)floor(verX)] != ' '))
		{

			if (settings->map[(int)floor(verY)][(int)floor(verX + (roundx - 1) )] == '1')
			{
				ray->verX = verX;
				ray->verY = verY;
				return ;
			}
			verX -= ray->value ;
			verY += ray->value *tan(ray->angle);
		 }
	ray->verX = MY_MAX_LIMIT;
	ray->verY = MY_MAX_LIMIT;
}
