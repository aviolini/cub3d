/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:37:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/22 14:55:33 by aviolini         ###   ########.fr       */
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

void	my_mlx_pixel_put3(img_data *img, double x, double y,double h, int color)
{
    char    *dst;
	double		i = 1;
	(void)i;
//	if (h < 0)
	//	h *=-1;
	while (--i < H_IMG/2 -h/2)
	{
    		dst = img->addr + ((int)(y + i) * img->line_length +
			(int)(x) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
	}
}

void	view_background(img_data *view)
{
	int x;
	int y;
	int z;
	unsigned int color;

	color = 0x00ffff00;
	y = -1;
	z = 3;

	while(--z > 0)
	{
		while(++y < (H_IMG/z) && -2 < (x = -1))
			while(++x < W_IMG)
				my_mlx_pixel_put(view,x,y,color);
		color = color >> 16;
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

void	set_ray(pl_data player, ray_data *ray)
{
	double verh;
	double horh;

		verh = hypot(fabs(player.posx - ray->verx), fabs(player.posy - ray->very));
		horh = hypot(fabs(player.posx - ray->horx), fabs(player.posy - ray->hory));

	if (horh <= verh)
		ray->distance = horh;
	else
		ray->distance = verh;
}
