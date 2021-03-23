/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:37:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/23 12:48:26 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_image(win_data *win, img_data *image)
{
	image->img = mlx_new_image(win->mlx, W_IMG, H_IMG);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
		&image->line_length, &image->endian);
}

void	my_mlx_pixel_put(img_data *img, int x, int y, int color)
{
    char    *dst;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	my_mlx_put_wall(win_data *win, img_data *img, int x, int color)
{
    char    *dst;
//	double	i = 0;
	double distprojplane;
	double perpdist;
	double h;
	double walltopy = 0, wallbottomy = 0;

	distprojplane = (W_IMG / 2)/tan(FOV/2);
	perpdist = win->ray.distance * (cos(win->ray.angle -win->player.angle));
	h = 1 / (perpdist) * distprojplane;
	h = (int)h;
	walltopy=H_IMG/2-h/2;
	walltopy = walltopy < 0 ? 0 : walltopy;
	wallbottomy = H_IMG / 2 + h  /2;
	wallbottomy = wallbottomy > H_IMG ? H_IMG : wallbottomy;
	//char *dst;
	int i = walltopy;

	while ((i) < wallbottomy)
	{
    		dst = img->addr + ((int)(i++) * img->line_length +
			(int)(x) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
	}
}

void	view_background(img_data *view, sett_data *settings)
{
	int x;
	int y;
	int z;
	unsigned int color;

	color = settings->ceiling_color;
	y = -1;
	z = 3;

	while(--z > 0)
	{
		while(++y < (H_IMG/z) && -2 < (x = -1))
			while(++x < W_IMG)
				my_mlx_pixel_put(view,x,y,color);
		color = settings->floor_color;
		y--;
	}
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

int	set_distance_and_wall_orientation(pl_data player, ray_data *ray)
{
	double	verh;
	double	horh;

	verh = hypot(fabs(player.posx - ray->verx), fabs(player.posy - ray->very));
	horh = hypot(fabs(player.posx - ray->horx), fabs(player.posy - ray->hory));
	if (horh <= verh)
	{
		ray->distance = horh;
		if (ray->diry < 0)
			return (1);
		else
			return (3);
	}
	else
	{
		ray->distance = verh;
		if(ray->dirx < 0)
			return (2) ;
		else
			return (0);
	}
	return (-1);
}
