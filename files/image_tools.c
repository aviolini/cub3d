/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:37:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/12 18:36:02 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	new_minimap_image(t_window *win, t_image *image)
{
	image->img = mlx_new_image(win->mlx, win->settings.mapW * SCALE, \
		 						win->settings.mapH * SCALE);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, \
								&image->line_length, &image->endian);
}

void	new_image(t_window *win, t_image *image)
{
	image->img = mlx_new_image(win->mlx, win->settings.winW, \
								win->settings.winH);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, \
								&image->line_length, &image->endian);
	win->settings.img_def = 1;
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	column(t_window *win, t_image *img, int x, int orientation)
{
	char			*dst;
	int				i;
	unsigned int	color;

	win->draw.perp_distance = win->ray.distance[x] * \
								(cos(win->ray.angle - win->player.angle));
	win->draw.h_object = 1 / win->draw.perp_distance * \
								win->draw.dist_proj_plane;
	win->draw.start_topY = win->settings.winH / 2 - win->draw.h_object / 2;
	win->draw.start_topY = win->draw.start_topY < 0 ? 0 : win->draw.start_topY;
	win->draw.end_bottomY = win->settings.winH / 2 + win->draw.h_object / 2;
	win->draw.end_bottomY = win->draw.end_bottomY > win->settings.winH ? win->settings.winH : win->draw.end_bottomY;
	i = win->draw.start_topY;
	while ((i) < win->draw.end_bottomY - 1)
	{
		win->draw.offsetY = (int)fabs((i + (win->draw.h_object / 2) - \
				(win->settings.winH / 2)) * \
				win->textures[orientation].texH / win->draw.h_object);
		color = *(win->textures[orientation].addr + \
			((int)(win->draw.offsetY) * win->textures[orientation].texH + \
			(int)((win->ray.indexTex - (int)win->ray.indexTex) * \
				win->textures[orientation].texW)));
		dst = img->addr + ((int)(i++) * img->line_length + \
				(int)(x) * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	open_texture(t_window *win, int i, char *path)
{
	win->textures[i].tex = mlx_xpm_file_to_image(win->mlx, path, \
							&win->textures[i].texW, &win->textures[i].texH);
	if (!win->textures[i].tex)
		return (0);
	return (1);
}

int	init_textures(t_window *win)
{
	int	i;
	int	useless_but_necessary_box[3];

	i = -1;
	if ((!open_texture(win, ++i, win->settings.east_texture)) || \
			(!open_texture(win, ++i, win->settings.north_texture)) || \
			(!open_texture(win, ++i, win->settings.west_texture)) || \
			(!open_texture(win, ++i, win->settings.south_texture)) || \
			(!open_texture(win, ++i, win->settings.sprite_texture)))
		return (0);
	i = -1;
	while (++i < 5)
	{
		if (!(win->textures[i].addr = \
							(int *)mlx_get_data_addr(win->textures[i].tex, \
							&useless_but_necessary_box[0], \
							&useless_but_necessary_box[1], \
							&useless_but_necessary_box[2])))
			return (0);
	}
	return (1);
}

void	view_background(t_image *view, t_settings *settings)
{
	unsigned int	x;
	unsigned int	y;
	int				z;
	unsigned int	color;

	color = settings->ceiling_color;
	y = 0;
	z = 3;

	while(--z > 0)
	{
		while(y < (settings->winH/z))
		{
			x = 0;
			while(x < settings->winW)
			{
				my_mlx_pixel_put(view,x,y,color);
				x++;
			}
			y++;
		}
		color = settings->floor_color;
		y--;
	}
}

void	set_right_resolution(t_window *win)
{
	int	myresx;
	int	myresy;

	mlx_get_screen_size(win->mlx, &myresx, &myresy);
	if((int)win->settings.winW > myresx)
		win->settings.winW = myresx;
	if((int)win->settings.winH > myresy)
		win->settings.winH = myresy;
	if ((int)win->settings.winW < MIN_RES_W || \
								(int)win->settings.winH < MIN_RES_H)
	{
		win->settings.winW = MIN_RES_W;
		win->settings.winH = MIN_RES_H;
	}
	win->draw.dist_proj_plane = (win->settings.winW / 2) / tan(FOV / 2);
}

void	print_intersection(t_window *win, double intersectionX, double intersectionY)
{
	if(win->settings.minimap_def)
		my_mlx_pixel_put(&win->world,intersectionX*SCALE, intersectionY*SCALE, RED);
}
int	set_distance_and_wall_orientation(t_window *win, t_player player, t_ray *ray,int i)
{
	double	ver_int;
	double	hor_int;

	ver_int = hypot(fabs(player.posX - ray->verX), fabs(player.posY - ray->verY));
	hor_int = hypot(fabs(player.posX - ray->horX), fabs(player.posY - ray->horY));
	if (hor_int <= ver_int)
	{
//		if(win->settings.minimap_def)
//			my_mlx_pixel_put(&win->world, ray->horX*SCALE, ray->horY*SCALE, RED);
		ray->distance[i] = hor_int;
		ray->indexTex = ray->horX;
		print_intersection(win,win->ray.horX,win->ray.horY);
//		if (ray->dirY < 0)
	//		return (1);
	//	else
	if (ray->dirY > 0)
			return (3);
	}
	else
	{
//		if(win->settings.minimap_def)
//			my_mlx_pixel_put(&win->world, ray->verX*SCALE, ray->verY*SCALE, RED);
		ray->indexTex = ray->verY;
		ray->distance[i] = ver_int;
		print_intersection(win,win->ray.verX,win->ray.verY);
		if(ray->dirX < 0)
			return (2) ;
		else
			return (0);
	}
	return (1);
}
