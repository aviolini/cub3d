/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 14:27:41 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	build_view(t_window *win)
{
	new_minimap_image(win, &win->world);
	if (win->settings.minimap_def)
		if (!build_world(&win->world, win->settings.map))
			return (0);
	view_background(&win->view, &win->settings);
	image(win);
	if (win->settings.minimap_def)
		miniray(win);
	if (!sprite(win))
		return (0);
	free(win->ray.distance);
	if (win->settings.save == 0)
	{
		mlx_put_image_to_window(win->mlx, win->win, win->view.img, 00, 0);
		if (win->settings.minimap_def)
			mlx_put_image_to_window(win->mlx, win->win, win->world.img, 20, 20);
		mlx_do_sync(win->mlx);
		mlx_destroy_image(win->mlx, win->world.img);
	}
	else
		ft_bitmap(win);
	return (1);
}

int	image(t_window *win)
{
	unsigned int	i;
	int				orientation;

	i = 0;
	win->ray.angle = win->player.angle + FOV / 2;
	win->ray.distance = (double *)malloc(sizeof(double) * win->settings.winW);
	while (i < win->settings.winW)
	{
		win->ray.dirX = cos(win->ray.angle);
		win->ray.dirY = -sin(win->ray.angle);
		check_hor_inters(&win->settings, win->player, &win->ray);
		check_ver_inters(&win->settings, win->player, &win->ray);
		orientation = set_dist_and_wall_orient(win, win->player, \
			 											&win->ray, i);
		column(win, &win->view, i, orientation);
		win->ray.angle -= FOV / win->settings.winW;
		i++;
	}
	return (1);
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

int	sprite(t_window *win)
{
	t_sprite	*vis_sprites;
	int			num_vis_sprites;
	int			i;

	vis_sprites = (t_sprite *)malloc(sizeof(t_sprite) * \
												win->settings.num_sprites);
	if (!vis_sprites)
		return (0);
	i = -1;
	num_vis_sprites = 0;
	visible_sprites(win, vis_sprites, &num_vis_sprites);
	sort_sprites(vis_sprites, num_vis_sprites);
	while (++i < num_vis_sprites)
	{
		settings_sprite(win, vis_sprites, i);
		show_sprites(win, vis_sprites, i);
	}
	free(vis_sprites);
	return (1);
}
