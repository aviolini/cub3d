/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_trash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:59:18 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/09 11:35:39 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_put_wall(t_window *win, t_image *img, int x, int color)
{
    char    *dst;
	(void) color;
//	double	i = 0;
	double distprojplane;
	double perpdist;
	double h;
	double walltopy = 0, wallbottomy = 0;

	distprojplane = (win->settings.winW / 2)/tan(FOV/2);
	perpdist = SCALE / win->ray.distance[x] * (cos(win->ray.angle -win->player.angle));
	h = 1 / (perpdist) * distprojplane;
	h = (int)h;
/////////////////////////////////////////////////////////////
	walltopy=win->settings.winH/2-h/2;
	walltopy = walltopy < 0 ? 0 : walltopy;
	wallbottomy = win->settings.winH / 2 + h  /2;
	wallbottomy = wallbottomy > win->settings.winH ? win->settings.winH : wallbottomy;
	//char *dst;
	int i = walltopy;
	//int z = 0;

//	unsigned int pixel;
	//double val = wallbottomy / 64;

	while ((i) < wallbottomy-1)
	{

		//	pixel = (unsigned int)win->texture[z].addr + ((int)(i) *  win->texture[z].line_length +
		//	(int)(x) * ( win->texture[z].bits_per_pixel / 8));

    		dst = img->addr + ((int)(i++) * img->line_length +
			(int)(x) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
	}
}


int 	set_wall_color(int o)
{
	if ( o == 0)
		return RED;
	if ( o == 1)
		return GREEN;
	if (o == 2)
		return PINK;
	if (o == 3)
		return CYAN;
	return BLACK;
}

int		build_world(t_image *world, char **map, t_player *player)
{
	int y;
	int x;
	//int def;

	y = -1;
	x = -1;
	while(map[++y] && -2 < (x = -1))
	{
		while(map[y][++x])
		{
			if (map[y][x] == '1' || map[y][x] == 'N'|| map[y][x] == 'S'|| map[y][x] == 'E'|| map[y][x] == 'W')
				my_mlx_pixel_wall(world, x * SCALE, y * SCALE,GRAY);
			else if(map[y][x] == '2'){
				my_mlx_pixel_put(world, x * SCALE + SCALE/2-1, y * SCALE+SCALE/2-1,0x00FFFF00);
				my_mlx_pixel_put(world, x * SCALE + SCALE/2, y * SCALE+SCALE/2,0x00FFFF00);
				my_mlx_pixel_put(world, x * SCALE + SCALE/2, y * SCALE+SCALE/2-1,0x00FFFF00);
				my_mlx_pixel_put(world, x * SCALE + SCALE/2-1, y * SCALE+SCALE/2,0x00FFFF00);

			}
			else if(map[y][x] == '0')
				my_mlx_pixel_grid(world, x * SCALE, y * SCALE,GRAY,WHITE);
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
	my_mlx_pixel_put(world, player->posX*SCALE, player->posY*SCALE,0x00ffffff);
	return (1);
}

void	ray(t_window *win)
{

	double rayx,rayy;

	rayx = win->player.posX;
	rayy = win->player.posY;
	while (win->settings.map[(int)floor(rayy / SCALE)]
		[(int)floor(rayx / SCALE)] != '1')
	{
		my_mlx_pixel_put(&win->world, rayx, rayy,0x00ffffff);
		rayx += win->player.dirX;
		rayy += win->player.dirY;
	}
}

void	bundle_ray(t_window *win)
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
	double	rayx,rayy,dirX,dirY;
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
		dirX = cos(angle);
		dirY = -sin(angle);
		rayx = win->player.posX;
		rayy = win->player.posY;
		while (win->settings.map[(int)floor(rayy / SCALE)]
			[(int)floor(rayx / SCALE)] != '1')
		{
			my_mlx_pixel_put(&win->world, rayx, rayy,0x00ffffff);
			rayx += dirX;
			rayy += dirY;
			dist++;
		}

		c++;
		h = (H_IMG/dist)*3;//*((W_IMG/2)/(tan(M_PI/6)));
		wally=H_IMG/2;

		//h *= W_IMG/(tan(M_PI/6));
	//	my_mlx_put_wall(&win->view, wallx, wally, h, 0x00FF0000);
		wallx++;

	}
}

void	print_settings(t_settings settings)
{
	printf("------settings------------------------\n");
	//int i = 0;
	//printf("*map: %i\n",*(settings->map));
	printf("w_win: %i\n",settings.winW);
	printf("h_win: %i\n",settings.winH);
	printf("no_te: %s\n",settings.north_texture);
	printf("we_te: %s\n",settings.west_texture);
	printf("ea_te: %s\n",settings.east_texture);
	printf("so_te: %s\n",settings.south_texture);
	printf("sp_te: %s\n",settings.sprite_texture);
	printf("flo_col: %i\n",settings.floor_color);
	printf("cei_col: %i\n",settings.ceiling_color);
	printf("mapW: %i\n",settings.mapW);
	printf("mapH: %i\n",settings.mapH);
	printf("eof: %i\n",settings.eof);
	printf("num_of_sprite: %i \n",settings.num_of_sprite);
	//while ((settings->map)[i])
	//	printf("mapp: %s\n",(settings->map)[i++]);
	while (*(settings.map))
	{
		printf("map: %s-\n",*(settings.map));
		(settings.map)++;
	}
	printf("-----------------------------------\n");
}

void	print_ray(t_ray ray)
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
	//printf("rayx: %lf\n",floor(ray.rayx));
	//printf("rayy: %lf\n",floor(ray.rayy));
	//	printf("speed: %d\n",player.speed);
	printf("-----------------------------------\n");
	printf("-----------------------------------\n");
}

void	print_tex(t_texture texture)
{
	printf("-----texture------------------------\n");

	printf("texW: %i\n",texture.texW);
	printf("texH: %i\n",texture.texH);
	//printf("posY_map: %i\n",texture.posY/SCALE);
	//printf("dirX: %lf\n",texture.dirX);
	//printf("dirY: %lf\n",texture.dirY);

	printf("-----------------------------------\n");
}

void	print_player(t_player player)
{
	printf("-----player------------------------\n");
	printf("player_angle : %lf\n",player.angle*180/M_PI);
	printf("posX: %lf\n",player.posX);
	printf("posY: %lf\n",player.posY);
	printf("posX_map: %lf\n",player.posX/SCALE);
	printf("posY_map: %lf\n",player.posY/SCALE);
	printf("dirX: %lf\n",player.dirX);
	printf("dirY: %lf\n",player.dirY);

	printf("-----------------------------------\n");
}

void	miniray(t_window *win)
{
	my_mlx_pixel_put(&win->world, win->player.posX*SCALE, win->player.posY*SCALE,0x00ffffff);
	int i = 0;
	double rayy = win->player.posY*SCALE, rayx = win->player.posX*SCALE;

	while (i++< 6)
	{
		rayy += win->player.dirY;
		rayx += win->player.dirX;
		my_mlx_pixel_put(&win->world, rayx, rayy,BLACK);
	}

}

void	my_mlx_pixel_wall(t_image *img, int x, int y, int color)
{
    char    *dst;
	int		i;
	int		z;

	i = -1;
	while (++i < SCALE && -2 < (z = -1))
	{
		while (++z < SCALE)
		{
    		dst = img->addr + ((i + y) * img->line_length +
			(x + z) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
		}
	}
}

void	my_mlx_pixel_grid(t_image *img, int x, int y, int grid_color, int internal_color)
{
    char    *dst;
	int		i = -1, z = -1;

	while (++i <= SCALE && -2 < ( z = -1))
		if(i == 0 || i == SCALE)
		{
			while (++z < SCALE)
			{
    			dst = img->addr + ((i + y) * img->line_length +
				(x + z) * (img->bits_per_pixel / 8));
    			*(unsigned int*)dst = grid_color;
			}
		}
		else
			while (++z <= SCALE){
				if(z == 0 || z == SCALE)
				{
    				dst = img->addr + ((i + y) * img->line_length +
					(x + z) * (img->bits_per_pixel / 8));
    				*(unsigned int*)dst = grid_color;
				}
				else
				{
					dst = img->addr + ((i + y) * img->line_length +
					(x + z) * (img->bits_per_pixel / 8));
    				*(unsigned int*)dst = internal_color;
				}
			}
}
