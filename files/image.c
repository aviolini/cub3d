/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/12 09:27:45 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



int		build_view(t_window *win)
{
	//int a;
//	mlx_clear_window(win->mlx,win->win);
//if(win->settings.minimap_def)
//if(win->settings.minimap_def)
	new_minimap_image(win, &win->world);
//	new_image(win, &win->view);
if(win->settings.minimap_def)
	if(!build_world(&win->world, win->settings.map, &win->player))
		return (0);
	//mlx_sync(MLX_SYNC_IMAGE_WRITABLE,win->view.img);
	view_background(&win->view, &win->settings);

	//int c = 0;
	//win->ray = (t_ray *)malloc(sizeof(t_ray)*win->settings.winW)
	//while (c < win->settings.winX)
	//	{
	//		win->ray[c]=(t_ray *)malloc(sizeof(t_ray))
	//	}

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
	//	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD,win->win);
		mlx_do_sync(win->mlx);
//if(win->settings.minimap_def)
//if(win->settings.minimap_def)
		mlx_destroy_image(win->mlx, win->world.img);
	}
	else
		ft_bitmap(win);
	//mlx_destroy_image(win->mlx, win->view.img);
//	mlx_destroy_image(win->mlx, win->world.img);
	return (1);
}

int		image(t_window *win)
{
	win->ray.angle = win->player.angle + FOV/2;
	unsigned int i = 0;

	//int color;
	int orientation;


	win->ray.distance = (double *)malloc(sizeof(double) * win->settings.winW);
	while (i < win->settings.winW)
	{

		win->ray.dirX = cos(win->ray.angle);
		win->ray.dirY = -sin(win->ray.angle);
		check_hor_intersection(win,&win->settings, win->player, &win->ray);
		check_ver_intersection(win,&win->settings, win->player, &win->ray);




		orientation = set_distance_and_wall_orientation(win,win->player,&win->ray,i);
	//	color = set_wall_color(orientation);
	//	my_mlx_put_wall(win, &win->view, x, color);
		column(win, &win->view,i,orientation);

	//	sprite
win->ray.angle -= FOV/win->settings.winW;
	i++;
	}
/*	int z = 0;
	while (win->sprite[z])
		{
			printf("X : %f\t Y: %f\n",win->sprite[z]->sprX, win->sprite[z]->sprY);
			printf("distance : %f\n",win->sprite[z]->distance);
			z++;
		}

		printf("\n\n");

		 z = 0;
		while (win->sprite[z])
			{
				printf("X : %f\t Y: %f\n",win->sprite[z]->sprX, win->sprite[z]->sprY);
				printf("distance : %f\n",win->sprite[z]->distance);
				z++;
			}
*/	return (1);
}

void	check_hor_intersection(t_window *win, t_settings *settings, t_player player, t_ray *ray)
{
	//TOGLIERE WIN DATA WIN , TOGLIERE MY_MLX_PIXEL_PUT
	int		roundy;
	double	horX;
	double	horY;
	(void)win;

	if(ray->dirY < 0)
	{
		roundy = 0;
		ray->value = 1;
	}
	else
	//if (ray->dirY > 0)
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
	//	if(win->settings.minimap_def)
	//		my_mlx_pixel_put(&win->world, horX*SCALE, horY*SCALE, RED);
			ray->horX = horX;
			ray->horY = horY;
			return ;
		}
		if (settings->map[(int)floor(horY)][(int)floor(horX)] == '2')
		{//if(win->settings.minimap_def)
		//	my_mlx_pixel_put(&win->world, horX*SCALE, horY*SCALE, RED);
		//	sprite_intersections(win, win->sprite, horX, horY,i);
		}
		//my_mlx_pixel_put(&win->world, horX*SCALE, horY*SCALE, WHITE);
	//	if (settings->map[(int)floor((horY) + (roundy - 1))][(int)floor(horX)] == ' ')
		//	break;
		horY -= ray->value;
		horX += ray->value/tan(ray->angle);
	}
	ray->horX = MY_MAX_LIMIT;
	ray->horY = MY_MAX_LIMIT;
}

void	check_ver_intersection(t_window *win,t_settings *settings, t_player player, t_ray *ray)
{
	(void)win;
	int		roundx;
	double	verX;
	double	verY;

	if(ray->dirX < 0)
	{
		roundx = 0;
		ray->value = 1;
	}
	//if (ray->dirX > 0)
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
			//if(win->settings.minimap_def)
			//	my_mlx_pixel_put(&win->world, verX*SCALE, verY*SCALE, RED);
				ray->verX = verX;
				ray->verY = verY;
				return ;
			}
			if (settings->map[(int)floor(verY)][(int)floor(verX)] == '2')
			{//if(win->settings.minimap_def)
				//sprite_intersections(win, win->sprite, verX, verY,i);
				//my_mlx_pixel_put(&win->world, verX*SCALE, verY*SCALE, RED);
			}
		//	if (settings->map[(int)floor(verY)][(int)floor(verX + (roundx - 1) )] == ' ')
		///		break;
			verX -= ray->value ;
			verY += ray->value *tan(ray->angle);
		 }
	ray->verX = MY_MAX_LIMIT;
	ray->verY = MY_MAX_LIMIT;
}
