/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:24:43 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/09 14:50:25 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		visible_sprites(t_window *win, t_sprite *visibleSprites,int *numVisibleSprites)
{
	int i;

	i = -1;
	//for (int i = 0; i < win->settings.num_of_sprite; i++)
	while (++i < win->settings.num_of_sprite)
	{
        float angleSpritePlayer = win->player.angle - atan2(win->player.posY - win->sprite[i]->sprY,
			win->sprite[i]->sprX - win->player.posX);
        if (angleSpritePlayer > M_PI)
            angleSpritePlayer -= M_PI * 2;
        if (angleSpritePlayer < -M_PI)
            angleSpritePlayer += M_PI * 2;
        angleSpritePlayer = fabs(angleSpritePlayer);
        const float EPSILON = 0.2;
		if (angleSpritePlayer < (FOV/2) + EPSILON)
		{
            win->sprite[i]->angle = angleSpritePlayer;
			 win->sprite[i]->distance = hypot(win->sprite[i]->sprX - win->player.posX, win->sprite[i]->sprY - win->player.posY);
			visibleSprites[*numVisibleSprites] = *win->sprite[i];
			(*numVisibleSprites)++;
        }
    }
	return (1);
}

void 	sort_sprite(t_sprite *visibleSprites,int numVisibleSprites)
{
	int			i;
	t_sprite	temp;

	i = -1;
	while(++i < numVisibleSprites-1)
		if (visibleSprites[i].distance < visibleSprites[i + 1].distance)
		{
			temp = visibleSprites[i + 1];
			visibleSprites[i + 1] = visibleSprites[i];
			visibleSprites[i] = temp;
			i = -1;
		}
}

void	settings_sprite(t_window *win, t_sprite *visibleSprites, int i)
{

        double distprojplane = (win->settings.winW / 2)/tan(FOV/2);
        visibleSprites[i].perpDistance = visibleSprites[i].distance * cos(visibleSprites[i].angle);
        visibleSprites[i].spriteHeight = (1 / visibleSprites[i].perpDistance) * distprojplane;
        visibleSprites[i].spriteWidth = visibleSprites[i].spriteHeight;
        visibleSprites[i].spriteTopY = (win->settings.winH / 2) - (visibleSprites[i].spriteHeight / 2);
        visibleSprites[i].spriteTopY = (visibleSprites[i].spriteTopY < 0) ? 0 : visibleSprites[i].spriteTopY;
        visibleSprites[i].spriteBottomY = (win->settings.winH / 2) + (visibleSprites[i].spriteHeight / 2);
        visibleSprites[i].spriteBottomY = (visibleSprites[i].spriteBottomY > win->settings.winH) ? win->settings.winH : visibleSprites[i].spriteBottomY;
        visibleSprites[i].angle = atan2(visibleSprites[i].sprY - win->player.posY, visibleSprites[i].sprX - win->player.posX) + win->player.angle;
        visibleSprites[i].spriteScreenPosX = tan(visibleSprites[i].angle) * distprojplane;
        visibleSprites[i].spriteLeftX = (win->settings.winW / 2) + visibleSprites[i].spriteScreenPosX- (visibleSprites[i].spriteWidth / 2);
        visibleSprites[i].spriteRightX = visibleSprites[i].spriteLeftX + visibleSprites[i].spriteWidth;
}

void	show_sprite(t_window *win,t_sprite *visibleSprites,int i)
{
	double			x;
	int				y;
	unsigned int	color;
	char			*dst;

	x = (visibleSprites[i].spriteLeftX);
	while (x < visibleSprites[i].spriteRightX)
	{
		float texelWidth = (win->texture[4].texW / visibleSprites[i].spriteWidth);
		int textureOffsetX = (x - visibleSprites[i].spriteLeftX) * texelWidth;
		y = visibleSprites[i].spriteTopY;
		while(y < visibleSprites[i].spriteBottomY)
		{
			if (x > 0 && x < win->settings.winW && y > 0 && y < win->settings.winH)
			{
				int distanceFromTop = y + (visibleSprites[i].spriteHeight / 2) - (win->settings.winH / 2);
				int textureOffsetY = distanceFromTop * (win->texture[4].texH / visibleSprites[i].spriteHeight);
				color = *(win->texture[4].addr + ((int)(textureOffsetY * win->texture[4].texH +
				(int)(((textureOffsetX))))));
				dst = win->view.addr + (int)(y) * win->view.line_length +
				(int)(x) * (win->view.bits_per_pixel / 8);
					if (visibleSprites[i].perpDistance < win->ray.distance[(int)x])
					{
								if (color >= 4278190080 || color == 0)
								dst = (char *)255;
								else
									*(unsigned int*)dst = color;
					}
			}
			y++;
		}
		x++;
	}
}

int		sprite(t_window *win)
{
    t_sprite visibleSprites[win->settings.num_of_sprite];
    int numVisibleSprites = 0;

	visible_sprites(win,visibleSprites,&numVisibleSprites);
	sort_sprite(visibleSprites,numVisibleSprites);
	int i = -1;
	while ( ++i < numVisibleSprites)
	{
		settings_sprite(win,visibleSprites,i);
		show_sprite(win,visibleSprites,i);
	}
	return (1);
}
