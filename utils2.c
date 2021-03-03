/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 19:09:02 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/03 08:50:40 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_keycode_left(win_data *win)
{
	ft_destroy_img(win);
	my_mlx_pixel_put2(win->img_s, win->map_s->posx--, win->map_s->posy, 0x00FFFFFF);
}

void	ft_keycode_up(win_data *win)
{
	ft_destroy_img(win);
	//ft_build_image(win);
	my_mlx_pixel_put2(win->img_s, win->map_s->posx, win->map_s->posy--, 0x00FFFFFF);
}

void	ft_keycode_right(win_data *win)
{
	ft_destroy_img(win);
	my_mlx_pixel_put2(win->img_s, win->map_s->posx++, win->map_s->posy, 0x00FFFFFF);
}

void	ft_keycode_down(win_data *win)
{
	ft_destroy_img(win);
	my_mlx_pixel_put2(win->img_s, win->map_s->posx, win->map_s->posy++, 0x00FFFFFF);
}
