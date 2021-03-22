/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/22 18:59:31 by aviolini         ###   ########.fr       */
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
	double h;
		int x = 0;
	double perpdist;
	double distprojplane;
	double walltopy = 0, wallbottomy = 0;
	while (i++ < W_IMG)
	{


	win->ray.dirx = cos(win->ray.angle);
	win->ray.diry = -sin(win->ray.angle);
	check_hor_intersection(win,&win->settings, win->player, &win->ray);
	check_ver_intersection(win,&win->settings, win->player, &win->ray);
	set_ray(win->player,&win->ray);

	//printf("win->ray.distance : %lf\n",win->ray.distance);
	perpdist = win->ray.distance * (cos(win->ray.angle -win->player.angle));
	//printf("perpdistance : %lf\n",perpdist);
	distprojplane = (W_IMG / 2)/tan(FOV/2);
	h = SCALE / (perpdist) * distprojplane;
	h = (int)h;
	//h = (H_IMG/perpdistance);//*((W_IMG/2)/(tan(M_PI/6)));
	walltopy=H_IMG/2-h/2;
	walltopy = walltopy < 0 ? 0 : walltopy;
	wallbottomy = H_IMG / 2 + h  /2;
	wallbottomy = wallbottomy > H_IMG ? H_IMG : wallbottomy;
	char *dst;
	int i = walltopy;

	while ((i) < wallbottomy)
	{
		dst = win->view.addr + ((int)(i) * win->view.line_length +
		(int)(x) * (win->view.bits_per_pixel / 8));
		if (win->ray.dirx > 0 && win->ray.diry > 0)
			*(unsigned int*)dst = RED;
		if (win->ray.dirx > 0 && win->ray.diry < 0)
			*(unsigned int*)dst = GREEN;
		if (win->ray.dirx < 0 && win->ray.diry > 0)
			*(unsigned int*)dst = PINK;
		if (win->ray.dirx < 0 && win->ray.diry < 0)
			*(unsigned int*)dst = CYAN;
		i++;
	}
	//h *= W_IMG/(tan(M_PI/6));
	//my_mlx_pixel_put3(&win->view, wallx, wally, h, 0x00FF0000);
	x++;
	//print_ray(win->ray);
win->ray.angle -= FOV/W_IMG;
	}
	return (1);
}

void	check_hor_intersection(win_data *win, sett_data *settings, pl_data player, ray_data *ray)
{
	//TOGLIERE WIN DATA WIN , TOGLIERE MY_MLX_PIXEL_PUT
	int		roundy;
	double	horx;
	double	hory;

	if (ray->diry < 0)
	{
		roundy = 0;
		hory = floor(player.posy / SCALE) * SCALE + roundy;
		horx = player.posx + (fabs((player.posy) - (hory))
					/ tan(ray->angle));

		while ((floor(hory/SCALE) >= 0 && floor(hory/SCALE) < settings->mapy) &&
				(floor(horx/SCALE) >= 0 && floor(horx/SCALE) < settings->mapx))
		{
			if (settings->map[(int)floor((hory)/SCALE-1)][(int)floor(horx/SCALE)] == '1')
			{
				my_mlx_pixel_put(&win->world, horx, hory, WHITE);
				ray->horx = horx;
				ray->hory = hory;
				return ;

			}
			my_mlx_pixel_put(&win->world, horx, hory, WHITE);
			hory -= SCALE;
			horx += SCALE/tan(ray->angle);
		}
	}
	if (ray->diry > 0)
	{
		roundy = SCALE;
		hory = floor(player.posy / SCALE) * SCALE + roundy;
		horx = player.posx + (fabs((player.posy) -(hory))
					/ tan(2 * M_PI - ray->angle));

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
			horx -= SCALE/tan(ray->angle);
			//horx += SCALE/tan(2 * M_PI - ray->angle);
		}
	}
	ray->horx = MY_MAX_LIMIT;
	ray->hory = MY_MAX_LIMIT;
}

void	check_ver_intersection(win_data *win,sett_data *settings, pl_data player, ray_data *ray)
{
	int		roundx;
	double	verx;
	double	very;



	//if ((player.angle >= 0 && player.angle < M_PI_2) || (player.angle > 3 * M_PI_2
	//	&& player.angle <= 2 * M_PI))
	if (ray->dirx > 0)
	{
		roundx = SCALE;
		verx = floor(player.posx / SCALE) * SCALE + roundx;
		very = player.posy + (fabs((player.posx) - (verx))
		* tan(M_PI * 2 - (ray->angle)));

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
			very -= SCALE*tan(ray->angle);
		//	very += SCALE*tan(M_PI * 2 - ray->angle);
		 }

	}

//	if(player.angle > M_PI_2 && player.angle < 3 * M_PI_2)
	if (ray->dirx < 0)
	{
		roundx = 0;
		verx = floor(player.posx / SCALE) * SCALE + roundx;
		very = player.posy + (fabs((player.posx) - (verx))
		* tan((ray->angle)));

		while((floor(very/SCALE) > 0 && floor(very/SCALE) < settings->mapy) &&
				(floor(verx/SCALE) > 0 && floor(verx/SCALE) < settings->mapx))
		{
			if (settings->map[(int)floor(very/SCALE)][(int)floor((verx)/SCALE-1)] == '1')
			{
				my_mlx_pixel_put(&win->world, verx, very,YELLOW);
				ray->verx = verx;
				ray->very = very;
				return ;
			}
			my_mlx_pixel_put(&win->world, verx, very,YELLOW);
			verx -= SCALE;
			very += SCALE*tan(ray->angle);
		}
	}
	ray->verx = MY_MAX_LIMIT;
	ray->very = MY_MAX_LIMIT;
}
