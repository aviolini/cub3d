/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:37:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/19 11:04:40 by aviolini         ###   ########.fr       */
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
	double		i = -1;
	(void)i;
//	if (h < 0)
	//	h *=-1;
	while (++i < h)
	{
    		dst = img->addr + ((int)(y -(h/2) + i) * img->line_length +
			(int)(x) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
	}
}

void	my_mlx_pixel_wall(img_data *img, int x, int y, int color)
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

void	my_mlx_pixel_grid(img_data *img, int x, int y, int color)
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
    			*(unsigned int*)dst = color;
			}
		}
		else
			while (++z <= SCALE)
				if(z == 0 || z == SCALE)
				{
    				dst = img->addr + ((i + y) * img->line_length +
					(x + z) * (img->bits_per_pixel / 8));
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
