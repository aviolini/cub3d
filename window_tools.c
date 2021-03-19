/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:13:56 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/19 18:05:20 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		build_world(img_data *world, char **map, pl_data *player)
{
	int y;
	int x;
	//int def;

	y = -1;
	x = -1;
	//def = 0;	//RIMETTERLO INSIEME A RETURN=0 (RIGA 35) PER IL CONTROLLO
				//DEI DOPPI CARATTERI
				//SE SI LASCIA PLAYER->DEF INIZIALIZZARLO
				//LA STRUTTURA PLAYER NON E' STATA INIZIALIZZATA
	while(map[++y] && -2 < (x = -1))
	{
		while(map[y][++x])
		{
			if (map[y][x] == '1')
				my_mlx_pixel_wall(world, x * SCALE, y * SCALE,0x000000ff);
			else if(map[y][x] == '2')
				my_mlx_pixel_put(world, x * SCALE, y * SCALE,0x00ff0000);
			else if(map[y][x] == '0')
				my_mlx_pixel_grid(world, x * SCALE, y * SCALE,0x00ff0000);
		//	else if(map[y][x] != ' ' && map[y][x] != '0')
		//	{
			//	if (player->def != 1)
			//	{
				//	return (0);
			//	build_player(map, x, y, player);

			//	player->def = 1;
			//}
		//	}
		}
	}
	my_mlx_pixel_put(world, player->posx, player->posy,0x00ffffff);
	return (1);
}
void	set_right_resolution(win_data *win)
{
	(void)win;
	/*
	int myresx;
	int myresy;
//	mlx_get_screen_size(win->mlx, &myresx, &myresy);
	if(win->settings.win_resx > myresx)
		win->settings.win_resx = myresx;
	if(win->settings.win_resy > myresy)
		win->settings.win_resy = myresy;
*/}

void	move(char **map, pl_data *player, char var)
{
	int		value;
	if (var == 'w')
		value = 1;
	if (var == 's')
		value = -1;
	player->posy += (value)*player->diry * SPEED;
	player->posx += (value)*player->dirx * SPEED;
	while(map[(int)floor(player->posy / SCALE)]
		[(int)floor(player->posx / SCALE)] == '1')
	{
		player->posy -= (value)*player->diry;
		player->posx -= (value)*player->dirx;
	}
}

void	slide(char **map, pl_data *player, char var)
{
	int		value;
	if (var == 'a')
		value = -1;
	if (var == 'd')
		value = 1;
	player->posy += (value) * player->dirx * SPEED;
	player->posx -= (value) * player->diry * SPEED;
	while(map[(int)floor(player->posy / SCALE)]
		[(int)floor(player->posx / SCALE)] == '1')
	{
		player->posy -= (value) * player->dirx;
		player->posx += (value) * player->diry;
	}
}

void	rotate(pl_data *player, char var)
{
	int		value;
	if (var == 'r')
		value = -1;
	if (var == 'l')
		value = 1;
	if (player->angle + (value) * ROTATION > 2 * M_PI)
		player->angle = (value) * ROTATION;
	else if (player->angle + (value) * ROTATION < 0)
		player->angle = 2 * M_PI + (value) * ROTATION;
	else
		player->angle += (value) * ROTATION;
	player->dirx = cos(player->angle);
	player->diry = -sin(player->angle);
}

void	ray(win_data *win)
{

	double rayx,rayy;

	rayx = win->player.posx;
	rayy = win->player.posy;
	while (win->settings.map[(int)floor(rayy / SCALE)]
		[(int)floor(rayx / SCALE)] != '1')
	{
		my_mlx_pixel_put(&win->world, rayx, rayy,0x00ffffff);
		rayx += win->player.dirx;
		rayy += win->player.diry;
	}
}

void	bundle_ray(win_data *win)
{
	/*
	c++;
	h = (H_IMG/dist);
	wally=H_IMG/2;
	h *=6;
	wallx++;
	my_mlx_pixel_put3(&win->view, wallx, wally, h, 0x00FF0000);
	*/
	double wally = 0, wallx = 0, h , dist = 1;

	double	angle;
	double	rayx,rayy,dirx,diry;
	double	rad;
	int		i;
	int		c;

	c = 0;
	i = 0;
	rad = FOV/W_IMG;
	angle = win->player.angle + FOV/2;
	while(i++ < W_IMG)
	{
		dist = 1;
		angle -= rad;
		dirx = cos(angle);
		diry = -sin(angle);
		rayx = win->player.posx;
		rayy = win->player.posy;
		while (win->settings.map[(int)floor(rayy / SCALE)]
			[(int)floor(rayx / SCALE)] != '1')
		{
			my_mlx_pixel_put(&win->world, rayx, rayy,0x00ffffff);
			rayx += dirx;
			rayy += diry;
			dist++;
		}

		c++;
		h = (H_IMG/dist)*3;//*((W_IMG/2)/(tan(M_PI/6)));
		wally=H_IMG/2;

		//h *= W_IMG/(tan(M_PI/6));
		my_mlx_pixel_put3(&win->view, wallx, wally, h, 0x00FF0000);
		wallx++;

	}
}

void	check_hor_intersection(win_data *win, sett_data *settings, pl_data player, ray_data *ray)
{
	//TOGLIERE WIN DATA WIN , TOGLIERE MY_MLX_PIXEL_PUT
	int		roundy;
	double	horx;
	double	hory;

	if (player.angle > 0 && player.angle < M_PI)
	{
		roundy = 0;
		hory = floor(player.posy / SCALE) * SCALE + roundy;
		horx = player.posx + (fabs((player.posy) - (hory))
					/ tan(player.angle));

		while ((floor(hory/SCALE) >= 0 && floor(hory/SCALE) < settings->mapy) &&
				(floor(horx/SCALE) >= 0 && floor(horx/SCALE) < settings->mapx))
		{
			if (settings->map[(int)floor(hory/SCALE)][(int)floor(horx/SCALE)] == '1')
			{
				my_mlx_pixel_put(&win->world, horx, hory, BLACK);
				ray->horx = horx;
				ray->hory = hory;
				return ;

			}
			my_mlx_pixel_put(&win->world, horx, hory, BLACK);
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
				my_mlx_pixel_put(&win->world, horx, hory, BLACK);
				ray->horx = horx;
				ray->hory = hory;
				return ;
			}
			my_mlx_pixel_put(&win->world, horx, hory, BLACK);
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
		roundx = 0;
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

void	set_ray(pl_data player, ray_data *ray)
{
	double verh;
	double horh;

	if (ray->verx >= 0 && ray->very >= 0)
		verh = hypot(fabs(player.posx - ray->verx), fabs(player.posy - ray->very));
	else
	{
		ray->rayx = ray->horx;
		ray->rayy = ray->hory;
		return ;
	}
	if (ray->horx >= 0 && ray->hory >= 0)
		horh = hypot(fabs(player.posx - ray->horx), fabs(player.posy - ray->hory));
	else
		{
			ray->rayx = ray->verx;
			ray->rayy = ray->very;
			return ;
		}
	if (horh <= verh)
		{
			ray->rayx = ray->horx;
			ray->rayy = ray->hory;
		}
	else
	{
		ray->rayx = ray->verx;
		ray->rayy = ray->very;
	}
}

void	init_ray(ray_data *ray)
{
	ray->rayx = 0;
	ray->rayy = 0;
}
