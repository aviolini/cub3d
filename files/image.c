/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/30 16:42:42 by aviolini         ###   ########.fr       */
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
	sprite(win);
	mlx_put_image_to_window(win->mlx, win->win, win->world.img, 05, 20);
	mlx_put_image_to_window(win->mlx, win->win, win->view.img, 700, 0);

mlx_destroy_image(win->mlx, win->world.img);
	mlx_destroy_image(win->mlx, win->view.img);

	return (1);
}

int		sprite(t_window *win)
{
//	double distprojplane;
//	double perpdist;

//	double walltopy = 0, wallbottomy = 0;

//	distprojplane = (W_IMG / 2)/tan(FOV/2);

//	perpdist =  win->ray.distance * (cos(win->ray.angle -win->player.angle));

	double max;
	int c;
	t_sprite *temp;
	max = 0;
	c = 0;

	while(c<win->settings.num_of_sprite && win->sprite[c]->distance > 0)
	{
//		printf("co\n\n");
		//c = 0;
		if (win->sprite[c]->distance < win->sprite[c + 1]->distance)
		{
//			printf("ciao\n\n");
			temp = 	win->sprite[c + 1];
			win->sprite[c + 1] = win->sprite[c];
			win->sprite[c] = temp;
			c = -1;
		}
		c++;
	}
	c = 0;


	double h;
	char *dst;
	unsigned int color;
	double distprojplane;
	double walltopy = 0, wallbottomy = 0;
	distprojplane = (W_IMG / 2)/tan(FOV/2);

	while(c<win->settings.num_of_sprite && win->sprite[c]->distance > 0)
	{

		h = 1/ win->sprite[c]->distance * distprojplane;
		walltopy=H_IMG/2-h/2;
		walltopy = walltopy < 0 ? 0 : walltopy;
		wallbottomy = H_IMG / 2 + h  /2;
		wallbottomy = wallbottomy > H_IMG ? H_IMG : wallbottomy;
		//char *dst;
		int u = 0;
		while(u++ < h )
	{
		int y = walltopy;
		int k = 0;


			while ((y) < wallbottomy)
		{

		color = *(win->texture[4].addr + ((int)(64/h*(k++)))*64 +
		(int)((u)%64));
	//	(int)((win->sprite[c]->sprX-(int)win->sprite[c]->sprX)*64)));

				dst = win->view.addr + (int)(y++) * win->view.line_length +
				(int)(win->sprite[c]->i + u) * (win->view.bits_per_pixel / 8);
				*(unsigned int*)dst = color;
		}

	//	win->sprite[c]->i++;

//mlx_put_image_to_window(win->mlx, win->win, win->texture[4].tex, win->sprite[c]->i, wallbottomy);
}
		//win->sprite[c]->distance = 0;
		win->sprite[c]->sprX = 0;
		win->sprite[c]->sprY = 0;
		win->sprite[c]->distance = 0;
		c++;

	}

	/*
	h = 1/ win->sprite[] * distprojplane;
	//h = H_IMG/perpdist;


	walltopy=H_IMG/2-h/2;
	walltopy = walltopy < 0 ? 0 : walltopy;
	wallbottomy = H_IMG / 2 + h  /2;
	wallbottomy = wallbottomy > H_IMG ? H_IMG : wallbottomy;
	//char *dst;
	int i = walltopy;
	int k = 0;


		while ((i) < wallbottomy)
	{
	color = *(win->texture[orientation].addr + ((int)(64/h*k++)*64 +
	(int)((win->ray.indexTex-(int)win->ray.indexTex)*64)));

    		dst = img->addr + ((int)(i++) * img->line_length +
			(int)(x) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
	}

*/
	return (1);
}

int		image(t_window *win)
{
	win->ray.angle = win->player.angle + FOV/2;
	int i = 0;

	//int color;
	int orientation;
	while (i++ < W_IMG)
	{
		win->ray.angle -= FOV/W_IMG;
		win->ray.dirX = cos(win->ray.angle);
		win->ray.dirY = -sin(win->ray.angle);
		check_hor_intersection(win,&win->settings, win->player, &win->ray,i);
		check_ver_intersection(win,&win->settings, win->player, &win->ray,i);




		orientation = set_distance_and_wall_orientation(win->player,&win->ray);
	//	color = set_wall_color(orientation);
	//	my_mlx_put_wall(win, &win->view, x, color);
		column(win, &win->view,i,orientation);

	//	sprite

	}
	int z = 0;
	while (win->sprite[z])
		{
			printf("X : %f\t Y: %f\n",win->sprite[z]->sprX, win->sprite[z]->sprY);
			printf("distance : %f\n",win->sprite[z]->distance);
			z++;
		}

		sprite(win);
		printf("\n\n");

		 z = 0;
		while (win->sprite[z])
			{
				printf("X : %f\t Y: %f\n",win->sprite[z]->sprX, win->sprite[z]->sprY);
				printf("distance : %f\n",win->sprite[z]->distance);
				z++;
			}
	return (1);
}

void	check_hor_intersection(t_window *win, t_settings *settings, t_player player, t_ray *ray,int i)
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
		if (settings->map[(int)floor(hory)][(int)floor(horx)] == '2')
			sprite_intersections(win, win->sprite, horx, hory,i);
		if (settings->map[(int)floor((hory) + (roundy - 1))][(int)floor(horx)] == '1')
		{
			my_mlx_pixel_put(&win->world, horx*SCALE, hory*SCALE, WHITE);
			ray->horx = horx;
			ray->hory = hory;
			return ;
		}


	//	my_mlx_pixel_put(&win->world, horx*SCALE, hory*SCALE, WHITE);
		hory -= ray->value_y;
		horx += ray->value_y/tan(ray->angle);
	}
	ray->horx = MY_MAX_LIMIT;
	ray->hory = MY_MAX_LIMIT;
}

void	check_ver_intersection(t_window *win,t_settings *settings, t_player player, t_ray *ray,int i)
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
			if (settings->map[(int)floor(very)][(int)floor(verx)] == '2')
				sprite_intersections(win, win->sprite, verx, very,i);
			if (settings->map[(int)floor(very)][(int)floor(verx + (roundx - 1) )] == '1')
			{
				my_mlx_pixel_put(&win->world, verx*SCALE, very*SCALE, YELLOW);
				ray->verx = verx;
				ray->very = very;
				return ;
			}
			//my_mlx_pixel_put(&win->world, verx*SCALE, very*SCALE, YELLOW);
			verx -= ray->value_x ;
			very += ray->value_x *tan(ray->angle);
		 }
	ray->verx = MY_MAX_LIMIT;
	ray->very = MY_MAX_LIMIT;
}
