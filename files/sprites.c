/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:24:43 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/07 09:32:19 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		visible_sprites(t_window *win, t_sprite *visibleSprites,int *numVisibleSprites)
{
	for (int i = 0; i < win->settings.num_of_sprite; i++)
	{
        float angleSpritePlayer = win->player.angle - atan2(win->player.posY - win->sprite[i]->sprY,
			win->sprite[i]->sprX - win->player.posX);
        if (angleSpritePlayer > M_PI)
            angleSpritePlayer -= M_PI * 2;
        if (angleSpritePlayer < -M_PI)
            angleSpritePlayer += M_PI * 2;
        angleSpritePlayer = fabs(angleSpritePlayer);

        // If sprite angle is less than half the FOV plus a small margin
        const float EPSILON = 0.1;

//		printf("angleSpritePlayer: %f\n",angleSpritePlayer);
		if (angleSpritePlayer < (FOV/2) + EPSILON)
		{
            win->sprite[i]->visible = 1;
            win->sprite[i]->angle = angleSpritePlayer;
			 win->sprite[i]->distance = hypot(win->sprite[i]->sprX - win->player.posX, win->sprite[i]->sprY - win->player.posY);
          //  win->sprite[i]->distance = hypot(fabs(win->sprite[i]->sprX - win->player.posX), //////////////////controlla ordine
			//							fabs(win->sprite[i]->sprY - win->player.posY));
			visibleSprites[*numVisibleSprites] = *win->sprite[i]; //////////////[0][i] oppure *
			(*numVisibleSprites)++;
        }
		else
		{
            win->sprite[i]->visible = 0;
        }
    }
//	printf("*numVisibleSprites : %d\n\n\n\n",*numVisibleSprites);
	return (1);
}

void 	sort_sprite(t_sprite *visibleSprites,int numVisibleSprites )
{
	for (int i = 0; i < numVisibleSprites - 1; i++)
 {
		for (int j = i + 1; j < numVisibleSprites; j++)
	 {
			if (visibleSprites[i].distance < visibleSprites[j].distance)
		 {
				t_sprite temp = visibleSprites[i];
				visibleSprites[i] = visibleSprites[j];
				visibleSprites[j] = temp;
			}
		}
	}
}

void	settings_sprite(t_window *win, t_sprite *visibleSprites, int i)
{

        	double distprojplane = (win->settings.winW / 2)/tan(FOV/2);
        // Calculate the perpendicular distance of the sprite to prevent fish-eye effect
        visibleSprites[i].perpDistance = visibleSprites[i].distance * cos(visibleSprites[i].angle);

        // Calculate the sprite projected height and width (the same, as sprites are squared)
        visibleSprites[i].spriteHeight = (1 / visibleSprites[i].perpDistance) * distprojplane;
        visibleSprites[i].spriteWidth = visibleSprites[i].spriteHeight;

        // Sprite top Y
        visibleSprites[i].spriteTopY = (win->settings.winH / 2) - (visibleSprites[i].spriteHeight / 2);
        visibleSprites[i].spriteTopY = (visibleSprites[i].spriteTopY < 0) ? 0 : visibleSprites[i].spriteTopY;

        // Sprite bottom Y
        visibleSprites[i].spriteBottomY = (win->settings.winH / 2) + (visibleSprites[i].spriteHeight / 2);
        visibleSprites[i].spriteBottomY = (visibleSprites[i].spriteBottomY > win->settings.winH) ? win->settings.winH : visibleSprites[i].spriteBottomY;

        // Calculate the sprite X position in the projection plane
        visibleSprites[i].angle = atan2(visibleSprites[i].sprY - win->player.posY, visibleSprites[i].sprX - win->player.posX) + win->player.angle;
        visibleSprites[i].spriteScreenPosX = tan(visibleSprites[i].angle) * distprojplane;

        // SpriteLeftX
	//	double var;
	//	visibleSprites[i].spriteLeftX;
	//	if (win->player.diry )
        	visibleSprites[i].spriteLeftX = (win->settings.winW / 2) + visibleSprites[i].spriteScreenPosX- (visibleSprites[i].spriteWidth / 2);
	//	else
		//	spriteLeftX = (win->settings.winW / 2) + spriteScreenPosX + 1;// (spriteWidth / 2);

        // SpriteRightX
        visibleSprites[i].spriteRightX = visibleSprites[i].spriteLeftX + visibleSprites[i].spriteWidth;

        // Query the width and height of the texture
       // int H_TEX = upng_get_width(textures[visibleSprites[i].texture]);
       // int 64 = upng_get_height(textures[sprite.texture]);

}

void	show_sprite(t_window *win,t_sprite *visibleSprites,int i)
{
	double x;
	int y;
	unsigned int color;

		char *dst;

	x = (visibleSprites[i].spriteLeftX);
	while (x < visibleSprites[i].spriteRightX)
	{
		float texelWidth = (W_TEX / visibleSprites[i].spriteWidth);
		int textureOffsetX = (x - visibleSprites[i].spriteLeftX) * texelWidth;
		y = visibleSprites[i].spriteTopY;
		while(y < visibleSprites[i].spriteBottomY)
		{
			if (x > 0 && x < win->settings.winW && y > 0 && y < win->settings.winH)
			{
				int distanceFromTop = y + (visibleSprites[i].spriteHeight / 2) - (win->settings.winH / 2);
				int textureOffsetY = distanceFromTop * (H_TEX / visibleSprites[i].spriteHeight);


				//int offsetY = (int)((y + (h / 2) - (win->settings.winH / 2))*H_TEX/h);
				color = *(win->texture[4].addr + ((int)(textureOffsetY*H_TEX +

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



    // Rendering all the visible sprites
/*    for (int i = 0; i < numVisibleSprites; i++)
	{
        t_sprite sprite = visibleSprites[i];

        // Calculate the perpendicular distance of the sprite to prevent fish-eye effect
        float perpDistance = sprite.distance * cos(sprite.angle);

        // Calculate the sprite projected height and width (the same, as sprites are squared)
        float spriteHeight = (1 / perpDistance) * distprojplane;
        float spriteWidth = spriteHeight;

        // Sprite top Y
        float spriteTopY = (win->settings.winH / 2) - (spriteHeight / 2);
        spriteTopY = (spriteTopY < 0) ? 0 : spriteTopY;

        // Sprite bottom Y
        float spriteBottomY = (win->settings.winH / 2) + (spriteHeight / 2);
        spriteBottomY = (spriteBottomY > win->settings.winH) ? win->settings.winH : spriteBottomY;

        // Calculate the sprite X position in the projection plane
        float spriteAngle = atan2(sprite.sprY - win->player.posY, sprite.sprX - win->player.posX) + win->player.angle;
        float spriteScreenPosX = tan(spriteAngle) * distprojplane;

        // SpriteLeftX
	//	double var;
		float spriteLeftX;
	//	if (win->player.diry )
        	spriteLeftX = (win->settings.winW / 2) + spriteScreenPosX- (spriteWidth / 2);
	//	else
		//	spriteLeftX = (win->settings.winW / 2) + spriteScreenPosX + 1;// (spriteWidth / 2);

        // SpriteRightX
        float spriteRightX = spriteLeftX + spriteWidth;

        // Query the width and height of the texture
       // int H_TEX = upng_get_width(textures[sprite.texture]);
       // int 64 = upng_get_height(textures[sprite.texture]);

        // Loop all the x values
        for (double x = spriteLeftX; x < spriteRightX; x++)
		{
            float texelWidth = (W_TEX / spriteWidth);
            int textureOffsetX = (x - spriteLeftX) * texelWidth;

		//	int offsetX = (x - left)*H_TEX/h;

            // Loop all the y values
            for (int y = spriteTopY; y < spriteBottomY; y++)
			{
                if (x > 0 && x < win->settings.winW && y > 0 && y < win->settings.winH)
				{
                    int distanceFromTop = y + (spriteHeight / 2) - (win->settings.winH / 2);
                    int textureOffsetY = distanceFromTop * (H_TEX / spriteHeight);


					//int offsetY = (int)((y + (h / 2) - (win->settings.winH / 2))*H_TEX/h);
					color = *(win->texture[4].addr + ((int)(textureOffsetY*H_TEX +

					(int)(((textureOffsetX))))));

					dst = win->view.addr + (int)(y) * win->view.line_length +
					(int)(x) * (win->view.bits_per_pixel / 8);

						if (perpDistance < win->ray.distance[(int)x])
						{
									if (color >= 4278190080 || color == 0)
									dst = (char *)255;
									else
										*(unsigned int*)dst = color;
						}

                  //  color_t* spriteTextureBuffer = (color_t*) upng_get_buffer(textures[sprite.texture]);
                    //color_t texelColor = spriteTextureBuffer[(H_TEX * textureOffsetY) + textureOffsetX];

                  //  if (sprite.distance < rays[x].distance && texelColor != 0xFFFF00FF)
				//	{
                     //   drawPixel(x, y, texelColor);
                  //  }
                }
            }
        }
    }
*/	return (1);
}
