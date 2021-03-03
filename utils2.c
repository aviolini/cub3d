/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:09:02 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/03 12:16:26 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_keycode_down(win_data *win)
{
	ft_destroy_img(win);
	ft_build_image(win,0);
	if (*(win->img_s->addr + ((win->map_s->posy + 1) * win->img_s->line_length +
			win->map_s->posx * (win->img_s->bits_per_pixel / 8))) == 0)
		{
			win->map_s->posy++;
			my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy , 0x00FFFFFF);
		}
		else
		my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy , 0x00FFFFFF);
}

void	ft_keycode_up(win_data *win)
{
	ft_destroy_img(win);
	ft_build_image(win,0);
	if (*(win->img_s->addr + ((win->map_s->posy - 1) * win->img_s->line_length +
			win->map_s->posx * (win->img_s->bits_per_pixel / 8))) == 0)
		{
			win->map_s->posy--;
			my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy , 0x00FFFFFF);
		}
	else
		my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy  , 0x00FFFFFF);
}

void	ft_keycode_right(win_data *win)
{
	ft_destroy_img(win);
	ft_build_image(win,0);
	if (*(win->img_s->addr + ((win->map_s->posy) * win->img_s->line_length +
			(win->map_s->posx + 1) * (win->img_s->bits_per_pixel / 8))) == 0)
		{
			win->map_s->posx++;
			my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy , 0x00FFFFFF);
		}
	else
		my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy  , 0x00FFFFFF);

}

void	ft_keycode_left(win_data *win)
{
	ft_destroy_img(win);
	ft_build_image(win,0);
	if (*(win->img_s->addr + ((win->map_s->posy) * win->img_s->line_length +
			(win->map_s->posx - 1) * (win->img_s->bits_per_pixel / 8))) == 0)
		{
			win->map_s->posx--;
			my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy , 0x00FFFFFF);
		}
	else
		my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy  , 0x00FFFFFF);

}
