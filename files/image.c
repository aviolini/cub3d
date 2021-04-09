/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/09 14:22:46 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	build_view(t_window *win)
{
	new_minimap_image(win, &win->world);
	if (win->settings.minimap_def)
		if (!build_world(&win->world, win->settings.map, &win->player))
			return (0);
	view_background(&win->view, &win->settings);
	image(win);
	if (win->settings.minimap_def)
		miniray(win);
	sprite(win);
	free(win->ray.distance);
	if (win->settings.save == 0)
	{
		mlx_put_image_to_window(win->mlx, win->win, win->view.img, 0, 0);
		if (win->settings.minimap_def)
			mlx_put_image_to_window(win->mlx, win->win, win->world.img, 20, 20);
		mlx_do_sync(win->mlx);
	}
	else
		ft_bitmap(win);
	mlx_destroy_image(win->mlx, win->world.img);
	return (1);
}

int	image(t_window *win)
{
	int	i;
	int	orientation;

	i = -1;
	win->ray.angle = win->player.angle + FOV / 2;
	win->ray.distance = (double *)malloc(sizeof(double) * win->settings.winW);
	while (++i < win->settings.winW)
	{
		win->ray.dirX = cos(win->ray.angle);
		win->ray.dirY = -sin(win->ray.angle);
		check_hor_intersection(win, &win->settings, win->player, &win->ray);
		check_ver_intersection(win, &win->settings, win->player, &win->ray);
		orientation = set_distance_and_wall_orientation \
		(win, win->player, &win->ray, i);
		column(win, &win->view, i, orientation);
		win->ray.angle -= FOV / win->settings.winW;
	}
	return (1);
}

void	check_hor_intersection(t_window *win, t_settings *settings, \
	t_player player, t_ray *ray)
{
	int		roundy;
	double	horx;
	double	hory;

	(void) win;
	if (ray->dirY < 0)
	{
		roundy = 0;
		ray->value_y = 1;
	}
	else
	{
		roundy = 1;
		ray->value_y = -1;
	}
	hory = floor(player.posY) + roundy;
	horx = player.posX + (fabs((player.posY) -(hory)) / \
		(ray->value_y * tan(ray->angle)));
	while (floor(horx) >= 0 && floor(horx) < settings->mapW && \
		(settings->map[(int)floor(hory)][(int)floor(horx)] != ' '))
	{
		if (settings->map[(int)floor((hory) + (roundy - 1))] \
							[(int)floor(horx)] == '1')
		{
			ray->horx = horx;
			ray->hory = hory;
			return ;
		}
		hory -= ray->value_y;
		horx += ray->value_y / tan(ray->angle);
	}
	ray->horx = MY_MAX_LIMIT;
	ray->hory = MY_MAX_LIMIT;
}

void	check_ver_intersection(t_window *win, t_settings *settings, \
	t_player player, t_ray *ray)
{
	int		roundx;
	double	verx;
	double	very;

	(void) win;
	if (ray->dirX < 0)
	{
		roundx = 0;
		ray->value_x = 1;
	}
	else
	{
		roundx = 1;
		ray->value_x = -1;
	}
	verx = floor(player.posX / 1) * 1 + roundx;
	very = player.posY + (fabs(player.posX - verx)) * \
			(ray->value_x * tan(ray->angle));
	while ((floor(very) >= 0 && floor(very) < settings->mapH) && \
			(settings->map[(int)floor(very)][(int)floor(verx)] != ' '))
	{
		if (settings->map[(int)floor(very)] \
							[(int)floor(verx + (roundx - 1))] == '1')
		{
			ray->verx = verx;
			ray->very = very;
			return ;
		}
		verx -= ray->value_x ;
		very += ray->value_x * tan(ray->angle);
	}
	ray->verx = MY_MAX_LIMIT;
	ray->very = MY_MAX_LIMIT;
}
