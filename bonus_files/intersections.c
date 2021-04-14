/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:26:25 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 14:28:09 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_hor_inters(t_settings *settings, t_player player, t_ray *ray)
{
	double	horX;
	double	horY;

	set_ray_round_and_ray_value(ray->dirY, ray);
	horY = floor(player.posY) + ray->round;
	horX = player.posX + (fabs((player.posY) -(horY)) / \
			(ray->value * tan(ray->angle)));
	while (floor(horX) >= 0 && floor(horX) < settings->mapW && \
			(settings->map[(int)floor(horY)][(int)floor(horX)] != ' '))
	{
		if (settings->map[(int)floor((horY) + (ray->round - 1))] \
							[(int)floor(horX)] == '1')
		{
			ray->horX = horX;
			ray->horY = horY;
			return ;
		}
		horY -= ray->value;
		horX += ray->value / tan(ray->angle);
	}
	ray->horX = MY_MAX_LIMIT;
	ray->horY = MY_MAX_LIMIT;
}

void	check_ver_inters(t_settings *settings, t_player player, t_ray *ray)
{
	double	verX;
	double	verY;

	set_ray_round_and_ray_value(ray->dirX, ray);
	verX = floor(player.posX) + ray->round;
	verY = player.posY + (fabs(player.posX - verX)) * \
							(ray->value * tan(ray->angle));
	while ((floor(verY) >= 0 && floor(verY) < settings->mapH) && \
			(settings->map[(int)floor(verY)][(int)floor(verX)] != ' '))
	{
		if (settings->map[(int)floor(verY)] \
							[(int)floor(verX + (ray->round - 1))] == '1')
		{
			ray->verX = verX;
			ray->verY = verY;
			return ;
		}
		verX -= ray->value ;
		verY += ray->value * tan(ray->angle);
	}
	ray->verX = MY_MAX_LIMIT;
	ray->verY = MY_MAX_LIMIT;
}

void	set_ray_round_and_ray_value(double dirXorY, t_ray *ray)
{
	if (dirXorY < 0)
	{
		ray->value = 1;
		ray->round = 0;
	}
	else
	{
		ray->value = -1;
		ray->round = 1;
	}
}

int	set_dist_and_wall_orient(t_window *win, t_player player, t_ray *ray, int i)
{
	double	ver_int;
	double	hor_int;

	ver_int = hypot(player.posX - ray->verX, player.posY - ray->verY);
	hor_int = hypot(player.posX - ray->horX, player.posY - ray->horY);
	if (hor_int <= ver_int)
	{
		ray->distance[i] = hor_int;
		ray->indexTex = ray->horX;
		print_intersection(win, win->ray.horX, win->ray.horY);
		if (ray->dirY > 0)
			return (3);
	}
	else
	{
		ray->indexTex = ray->verY;
		ray->distance[i] = ver_int;
		print_intersection(win, win->ray.verX, win->ray.verY);
		if (ray->dirX < 0)
			return (2);
		else
			return (0);
	}
	return (1);
}
