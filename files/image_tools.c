/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:37:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 10:50:09 by aviolini         ###   ########.fr       */
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

double draw_protect_max(double *value, unsigned int *max)
{
	if (*value > *max)
	 	*value = *max;
	else
		*value = *value;
	return (*value);
}

double	draw_protect_min(double *value)
{
	if (*value < 0)
		*value = 0;
	else
		*value = *value;
	return (*value);
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
	win->draw.start_topY = draw_protect_min(&win->draw.start_topY);
	win->draw.end_bottomY = win->settings.winH / 2 + win->draw.h_object / 2;
	win->draw.end_bottomY = draw_protect_max(&win->draw.end_bottomY, \
								&win->settings.winH);
	i = win->draw.start_topY;
	while ((i) < win->draw.end_bottomY - 1)
	{
		win->draw.offsetY = (int)fabs((i + (win->draw.h_object / 2) - \
				(win->settings.winH / 2)) * \
				win->textures[orientation].texH / win->draw.h_object);
		color = *(win->textures[orientation].addr + \
			(win->textures[orientation].texH * (int)(win->draw.offsetY) + \
			(int)((win->ray.indexTex - (int)win->ray.indexTex) * \
				win->textures[orientation].texW)));
		dst = img->addr + (img->line_length * (int)(i++) + \
				(img->bits_per_pixel / 8) * (int)(x));
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
		win->textures[i].addr = \
							(int *)mlx_get_data_addr(win->textures[i].tex, \
							&useless_but_necessary_box[0], \
							&useless_but_necessary_box[1], \
							&useless_but_necessary_box[2]);
		if (!win->textures[i].addr)
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
	while (--z > 0)
	{
		while (y < (settings->winH / z))
		{
			x = 0;
			while (x < settings->winW)
			{
				my_mlx_pixel_put(view, x, y, color);
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
	if ((int)win->settings.winW > myresx)
		win->settings.winW = myresx;
	if ((int)win->settings.winH > myresy)
		win->settings.winH = myresy;
	if ((int)win->settings.winW < MIN_RES_W || \
								(int)win->settings.winH < MIN_RES_H)
	{
		win->settings.winW = MIN_RES_W;
		win->settings.winH = MIN_RES_H;
	}
	win->draw.dist_proj_plane = (win->settings.winW / 2) / tan(FOV / 2);
}

void	print_intersection(t_window *win, double intersX, double intersY)
{
	if (win->settings.minimap_def)
		my_mlx_pixel_put(&win->world, intersX * SCALE, intersY * SCALE, RED);
}

int	set_distance_and_wall_orientation(t_window *win, t_player player, t_ray *ray, int i)
{
	double	ver_int;
	double	hor_int;

	ver_int = hypot(fabs(player.posX - ray->verX), fabs(player.posY - ray->verY));
	hor_int = hypot(fabs(player.posX - ray->horX), fabs(player.posY - ray->horY));
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
