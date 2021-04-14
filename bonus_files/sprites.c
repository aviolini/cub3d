/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:24:43 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 13:51:00 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	visible_sprites(t_window *win, t_sprite *vis_sprites, int *num_vis_sprites)
{
	int		i;
	double	angleSpritePlayer;

	i = 0;
	while (i < win->settings.num_sprites)
	{
		angleSpritePlayer = win->player.angle - \
					atan2(win->player.posY - win->sprites[i]->sprY, \
					win->sprites[i]->sprX - win->player.posX);
		if (angleSpritePlayer > M_PI)
			angleSpritePlayer -= M_PI * 2;
		if (angleSpritePlayer < -M_PI)
			angleSpritePlayer += M_PI * 2;
		angleSpritePlayer = fabs(angleSpritePlayer);
		if (angleSpritePlayer < (FOV / 2) + 0.2)
		{
			win->sprites[i]->angle = angleSpritePlayer;
			win->sprites[i]->distance = hypot(win->sprites[i]->sprX - \
				win->player.posX, win->sprites[i]->sprY - win->player.posY);
			vis_sprites[*num_vis_sprites] = *win->sprites[i];
			(*num_vis_sprites)++;
		}
		i++;
	}
	return (1);
}

void 	sort_sprites(t_sprite *vis_sprites, int num_vis_sprites)
{
	int			i;
	t_sprite	temp;

	i = -1;
	while (++i < num_vis_sprites - 1)
	{
		if (vis_sprites[i].distance < vis_sprites[i + 1].distance)
		{
			temp = vis_sprites[i + 1];
			vis_sprites[i + 1] = vis_sprites[i];
			vis_sprites[i] = temp;
			i = -1;
		}
	}
}

void	settings_sprite(t_window *win, t_sprite *vis_sprites, int i)
{
	vis_sprites[i].perp_distance = vis_sprites[i].distance * \
									cos(vis_sprites[i].angle);
	vis_sprites[i].sprite_height = (1 / vis_sprites[i].perp_distance) * \
									win->draw.dist_proj_plane;
	vis_sprites[i].sprite_width = vis_sprites[i].sprite_height;
	vis_sprites[i].sprite_topY = (win->settings.winH / 2) - \
									(vis_sprites[i].sprite_height / 2);
	vis_sprites[i].sprite_topY = draw_protect_min(&vis_sprites[i].sprite_topY);
	vis_sprites[i].sprite_bottomY = (win->settings.winH / 2) + \
									(vis_sprites[i].sprite_height / 2);
	vis_sprites[i].sprite_bottomY = draw_protect_max(\
									&vis_sprites[i].sprite_bottomY, \
									&win->settings.winH);
	vis_sprites[i].angle = atan2(vis_sprites[i].sprY - win->player.posY, \
				vis_sprites[i].sprX - win->player.posX) + win->player.angle;
	vis_sprites[i].sprite_screen_posX = tan(vis_sprites[i].angle) * \
									win->draw.dist_proj_plane;
	vis_sprites[i].sprite_leftX = (win->settings.winW / 2) + \
									vis_sprites[i].sprite_screen_posX - \
									(vis_sprites[i].sprite_width / 2);
	vis_sprites[i].sprite_rightX = vis_sprites[i].sprite_leftX + \
									vis_sprites[i].sprite_width;
}

void	draw_sprite_pixel(t_window *win, int x, int y)
{
	unsigned int	color;
	char			*dst;

	color = *(win->textures[4].addr + \
				((int)(win->draw.offsetY * win->textures[4].texH + \
				(int)(((win->draw.offsetX))))));
	dst = win->view.addr + win->view.line_length * (int)(y) + \
				(win->view.bits_per_pixel / 8) * (int)(x);
	if (color == 0 || color >= 4278190080)
		dst = (char *) 255;
	else
		*(unsigned int *)dst = color;
}

void	show_sprites(t_window *win, t_sprite *vis_sprites, int i)
{
	double	x;
	int		y;

	x = (vis_sprites[i].sprite_leftX);
	while (x < vis_sprites[i].sprite_rightX)
	{
		win->draw.texel_width = (win->textures[4].texW / \
										vis_sprites[i].sprite_width);
		win->draw.offsetX = (x - vis_sprites[i].sprite_leftX) * \
										win->draw.texel_width;
		y = vis_sprites[i].sprite_topY;
		while (y < vis_sprites[i].sprite_bottomY)
		{
			if (x > 0 && (int)x < (int)win->settings.winW && \
				y > 0 && y < (int)win->settings.winH && \
				(vis_sprites[i].perp_distance < win->ray.distance[(int)x]))
			{
				win->draw.distance_from_top = y + \
								(vis_sprites[i].sprite_height / 2) - \
								(win->settings.winH / 2);
				win->draw.offsetY = win->draw.distance_from_top * \
								(win->textures[4].texH / \
								vis_sprites[i].sprite_height);
				draw_sprite_pixel(win, x, y);
			}
			y++;
		}
		x++;
	}
}
