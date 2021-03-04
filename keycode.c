/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:09:02 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/04 16:43:44 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	ft_keycode_up(win_data *win)
{
	ft_destroy_img(win);
	ft_build_image(win,0);

	double posx, posy;
	posx = win->map_s->posx;
	posy = win->map_s->posy;
	posy -= pow(win->map_s->diry,2)* win->map_s->diry;
	posx += pow(win->map_s->dirx,2)* win->map_s->dirx;
	if (*(win->img_s->addr + ((int)posy * win->img_s->line_length +
	(int)posx * (win->img_s->bits_per_pixel / 8))) == 0)
	{
		win->map_s->posy-=pow(win->map_s->diry,2)* win->map_s->diry;
		win->map_s->posx+=pow(win->map_s->dirx,2)* win->map_s->dirx;
	//IL PERSONAGGIO:
	//	my_mlx_pixel_put(win->img_s,win->map_s->posy, win->map_s->posx , 0x00FFFFFF);
	}

}

void	ft_keycode_down(win_data *win)
{
	ft_destroy_img(win);
	ft_build_image(win,0);

	double posx, posy;
	posx = win->map_s->posx;
	posy = win->map_s->posy;
	posy += pow(win->map_s->diry,2)* win->map_s->diry;
	posx -= pow(win->map_s->dirx,2)* win->map_s->dirx;
	if (*(win->img_s->addr + ((int)posy * win->img_s->line_length +
	(int)posx * (win->img_s->bits_per_pixel / 8))) == 0)
	{
		win->map_s->posy+=pow(win->map_s->diry,2)* win->map_s->diry;
		win->map_s->posx-=pow(win->map_s->dirx,2)* win->map_s->dirx;
	//IL PERSONAGGIO:
	//	my_mlx_pixel_put(win->img_s,win->map_s->posy, win->map_s->posx , 0x00FFFFFF);
	}
	//else
	//	my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy  , 0x00FFFFFF);
}

void	ft_keycode_right(win_data *win)
{
	ft_destroy_img(win);
	ft_build_image(win,0);
	int posx, posy;
	int dirx, diry;

	posx = win->map_s->posx;
	posy = win->map_s->posy;

	diry = (win->map_s->diry - win->map_s->dirx) * pow(win->map_s->dirx,2) ;
	dirx = win->map_s->diry;

	posy -= pow(diry,2)* diry;
	posx += pow(dirx,2)* dirx;

	if (*(win->img_s->addr + ((posy) * win->img_s->line_length +
	posx * (win->img_s->bits_per_pixel / 8))) == 0)
	{
		win->map_s->posy-=pow(diry,2)* diry;
		win->map_s->posx+=pow(dirx,2)* dirx;
		my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy , 0x00FFFFFF);
	}
	else
		my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy  , 0x00FFFFFF);

}

void	ft_keycode_left(win_data *win)
{
	ft_destroy_img(win);
	ft_build_image(win,0);
	int posx, posy;
	int dirx, diry;

	posx = win->map_s->posx;
	posy = win->map_s->posy;

	diry = (win->map_s->diry - win->map_s->dirx) * pow(win->map_s->dirx,2) ;
	dirx = win->map_s->diry;

	posy += pow(diry,2)* diry;
	posx -= pow(dirx,2)* dirx;

	if (*(win->img_s->addr + ((posy) * win->img_s->line_length +
	posx * (win->img_s->bits_per_pixel / 8))) == 0)
	{
		win->map_s->posy+=pow(diry,2)* diry;
		win->map_s->posx-=pow(dirx,2)* dirx;
		my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy , 0x00FFFFFF);
	}
	else
		my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy  , 0x00FFFFFF);

}

void	ft_arrow_right(win_data *win)
{
	ft_destroy_img(win);
	ft_build_image(win,0);
	if (win->map_s->angle <= 0)
		win->map_s->angle = 2*M_PI;
	win->map_s->angle -= M_PI/4;
	//FORMULA DI ROTAZIONE PRECEDENTE
//	int temp;
//	temp = win->map_s->diry;
///	win->map_s->diry = (win->map_s->diry - win->map_s->dirx) * pow(win->map_s->dirx,2) ;
//	win->map_s->dirx =  temp;
	win->map_s->dirx = cos(win->map_s->angle);
	win->map_s->diry = sin(win->map_s->angle);
}

void	ft_arrow_left(win_data *win)
{
	ft_destroy_img(win);
	ft_build_image(win,0);
	if (win->map_s->angle >= 2*M_PI)
		win->map_s->angle = 0;
	win->map_s->angle += M_PI/4;
	//FORMULA DI ROTAZIONE PRECEDENTE
	//int temp;
	//temp = win->map_s->dirx;
	//win->map_s->dirx = (win->map_s->dirx - win->map_s->diry) * pow(win->map_s->diry,2) ;
	//win->map_s->diry =  temp;
	win->map_s->dirx = cos(win->map_s->angle);
	win->map_s->diry = sin(win->map_s->angle);
}
