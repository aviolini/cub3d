/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:20:09 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/14 09:06:18 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	draw_protect_max(double *value, unsigned int *max)
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

void	set_right_resolution(t_window *win)
{
	int	myresx;
	int	myresy;

	mlx_get_screen_size(win->mlx, &myresx, &myresy);
	if ((int)win->settings.winW < MIN_RES_W || \
								(int)win->settings.winH < MIN_RES_H)
	{
		win->settings.winW = MIN_RES_W;
		win->settings.winH = MIN_RES_H;
	}
	if ((int)win->settings.winW > myresx)
		win->settings.winW = myresx;
	if ((int)win->settings.winH > myresy)
		win->settings.winH = myresy;
	win->draw.dist_proj_plane = (win->settings.winW / 2) / tan(FOV / 2);
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
