/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/21 16:06:57 by aviolini         ###   ########.fr       */
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

void	check_hor_intersection(win_data *win, sett_data *settings, pl_data player, ray_data *ray)
{
	//TOGLIERE WIN DATA WIN , TOGLIERE MY_MLX_PIXEL_PUT
	int		roundy;
	double	horx;
	double	hory;

	if (player.angle > 0 && player.angle < M_PI)
	{
		roundy = -1;
		hory = floor(player.posy / SCALE) * SCALE + roundy;
		horx = player.posx + (fabs((player.posy) - (hory))
					/ tan(player.angle));

		while ((floor(hory/SCALE) >= 0 && floor(hory/SCALE) < settings->mapy) &&
				(floor(horx/SCALE) >= 0 && floor(horx/SCALE) < settings->mapx))
		{
			if (settings->map[(int)floor(hory/SCALE)][(int)floor(horx/SCALE)] == '1')
			{
				my_mlx_pixel_put(&win->world, horx, hory, WHITE);
				ray->horx = horx;
				ray->hory = hory;
				return ;

			}
			my_mlx_pixel_put(&win->world, horx, hory, WHITE);
			hory -= SCALE;
			horx += SCALE/tan(player.angle);
		}
	}
	if (player.angle > M_PI && player.angle < M_PI * 2)
	{
		roundy = SCALE;
		hory = floor(player.posy / SCALE) * SCALE + roundy;
		horx = player.posx + (fabs((player.posy) -(hory))
					/ tan(2 * M_PI - player.angle));

		while ((floor(hory/SCALE) > 0 && floor(hory/SCALE) < settings->mapy) &&
				(floor(horx/SCALE) > 0 && floor(horx/SCALE) < settings->mapx))
		{
			if (settings->map[(int)floor(hory/SCALE)][(int)floor(horx/SCALE)] == '1')
			{
				my_mlx_pixel_put(&win->world, horx, hory, WHITE);
				ray->horx = horx;
				ray->hory = hory;
				return ;
			}
			my_mlx_pixel_put(&win->world, horx, hory, WHITE);
			hory += SCALE;
			horx += SCALE/tan(2 * M_PI - player.angle);
		}
	}
	ray->horx = -1;
	ray->hory = -1;
}

void	check_ver_intersection(win_data *win,sett_data *settings, pl_data player, ray_data *ray)
{
	int		roundx;
	double	verx;
	double	very;



	if ((player.angle >= 0 && player.angle < M_PI_2) || (player.angle > 3 * M_PI_2
		&& player.angle <= 2 * M_PI))
	{
		roundx = SCALE;
		verx = floor(player.posx / SCALE) * SCALE + roundx;
		very = player.posy + (fabs((player.posx) - (verx))
		* tan(M_PI * 2 - (player.angle)));

		while((floor(very/SCALE) > 0 && floor(very/SCALE) < settings->mapy) &&
				(floor(verx/SCALE) > 0 && floor(verx/SCALE) < settings->mapx))
		{
			if (settings->map[(int)floor(very/SCALE)][(int)floor(verx/SCALE)] == '1')
			{
				my_mlx_pixel_put(&win->world, verx, very, YELLOW);
				ray->verx = verx;
				ray->very = very;
				return ;

			}
			my_mlx_pixel_put(&win->world, verx, very, YELLOW);
			verx += SCALE;
			very += SCALE*tan(M_PI * 2 - player.angle);
		 }

	}

	if(player.angle > M_PI_2 && player.angle < 3 * M_PI_2)
	{
		roundx = -1;
		verx = floor(player.posx / SCALE) * SCALE + roundx;
		very = player.posy + (fabs((player.posx) - (verx))
		* tan((player.angle)));

		while((floor(very/SCALE) > 0 && floor(very/SCALE) < settings->mapy) &&
				(floor(verx/SCALE) > 0 && floor(verx/SCALE) < settings->mapx))
		{
			if (settings->map[(int)floor(very/SCALE)][(int)floor(verx/SCALE)] == '1')
			{
				my_mlx_pixel_put(&win->world, verx, very,YELLOW);
				ray->verx = verx;
				ray->very = very;
				return ;
			}
			my_mlx_pixel_put(&win->world, verx, very,YELLOW);
			verx -= SCALE;
			very += SCALE*tan(player.angle);
		}
	}
	ray->verx = -1;
	ray->very = -1;
}
