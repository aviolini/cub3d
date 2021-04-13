/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:37:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 14:28:45 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
