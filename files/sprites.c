/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:24:43 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/11 22:39:13 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		visible_sprites(t_window *win, t_sprite *vis_sprites,int *num_vis_sprites)
{
	for (int i = 0; i < win->settings.num_sprites; i++)
	{
        float angleSpritePlayer = win->player.angle - atan2(win->player.posY - win->sprite[i]->sprY,
			win->sprite[i]->sprX - win->player.posX);
        if (angleSpritePlayer > M_PI)
            angleSpritePlayer -= M_PI * 2;
        if (angleSpritePlayer < -M_PI)
            angleSpritePlayer += M_PI * 2;
        angleSpritePlayer = fabs(angleSpritePlayer);

        // If sprite angle is less than half the FOV plus a small margin
        const float EPSILON = 0.2;

//		printf("angleSpritePlayer: %f\n",angleSpritePlayer);
		if (angleSpritePlayer < (FOV/2) + EPSILON)
		{
    //        win->sprite[i]->visible = 1;
            win->sprite[i]->angle = angleSpritePlayer;
			 win->sprite[i]->distance = hypot(win->sprite[i]->sprX - win->player.posX, win->sprite[i]->sprY - win->player.posY);
          //  win->sprite[i]->distance = hypot(fabs(win->sprite[i]->sprX - win->player.posX), //////////////////controlla ordine
			//							fabs(win->sprite[i]->sprY - win->player.posY));
			vis_sprites[*num_vis_sprites] = *win->sprite[i]; //////////////[0][i] oppure *
			(*num_vis_sprites)++;
        }
	//	else
	//	{
      //    win->sprite[i]->visible = 0;
       // }
    }
//	printf("*num_vis_sprites : %d\n\n\n\n",*num_vis_sprites);
	return (1);
}

void 	sort_sprite(t_sprite *vis_sprites,int num_vis_sprites)
{
	int			i;
	t_sprite	temp;

	i = -1;
	while(++i < num_vis_sprites-1)
		if (vis_sprites[i].distance < vis_sprites[i + 1].distance)
		{
			temp = vis_sprites[i + 1];
			vis_sprites[i + 1] = vis_sprites[i];
			vis_sprites[i] = temp;
			i = -1;
		}
}

void	settings_sprite(t_window *win, t_sprite *vis_sprites, int i)
{

        //	double distprojplane = (win->settings.winW / 2)/tan(FOV/2);
        // Calculate the perpendicular distance of the sprite to prevent fish-eye effect
        vis_sprites[i].perpDistance = vis_sprites[i].distance * cos(vis_sprites[i].angle);

        // Calculate the sprite projected height and width (the same, as sprites are squared)
        vis_sprites[i].spriteHeight = (1 / vis_sprites[i].perpDistance) * win->draw.dist_proj_plane;
        vis_sprites[i].spriteWidth = vis_sprites[i].spriteHeight;

        // Sprite top Y
        vis_sprites[i].spriteTopY = (win->settings.winH / 2) - (vis_sprites[i].spriteHeight / 2);
    //    vis_sprites[i].spriteTopY = (vis_sprites[i].spriteTopY < 0) ? 0 : vis_sprites[i].spriteTopY;

        // Sprite bottom Y
        vis_sprites[i].spriteBottomY = (win->settings.winH / 2) + (vis_sprites[i].spriteHeight / 2);
      //  vis_sprites[i].spriteBottomY = (vis_sprites[i].spriteBottomY > win->settings.winH) ? win->settings.winH : vis_sprites[i].spriteBottomY;

        // Calculate the sprite X position in the projection plane
        vis_sprites[i].angle = atan2(vis_sprites[i].sprY - win->player.posY, vis_sprites[i].sprX - win->player.posX) + win->player.angle;
        vis_sprites[i].spriteScreenPosX = tan(vis_sprites[i].angle) * win->draw.dist_proj_plane;

        // SpriteLeftX
	//	double var;
	//	vis_sprites[i].spriteLeftX;
	//	if (win->player.diry )
        	vis_sprites[i].spriteLeftX = (win->settings.winW / 2) + vis_sprites[i].spriteScreenPosX- (vis_sprites[i].spriteWidth / 2);
	//	else
		//	spriteLeftX = (win->settings.winW / 2) + spriteScreenPosX + 1;// (spriteWidth / 2);

        // SpriteRightX
        vis_sprites[i].spriteRightX = vis_sprites[i].spriteLeftX + vis_sprites[i].spriteWidth;

        // Query the width and height of the texture
       // int H_TEX = upng_get_width(textures[vis_sprites[i].texture]);
       // int 64 = upng_get_height(textures[sprite.texture]);

}

void	show_sprite(t_window *win,t_sprite *vis_sprites,int i)
{
	double x;
	int y;
	unsigned int color;

		char *dst;

	x = (vis_sprites[i].spriteLeftX);
	while (x < vis_sprites[i].spriteRightX)
	{
		float texelWidth = (win->texture[4].texW / vis_sprites[i].spriteWidth);
		int textureOffsetX = (x - vis_sprites[i].spriteLeftX) * texelWidth;
		y = vis_sprites[i].spriteTopY;
		while(y < vis_sprites[i].spriteBottomY)
		{
			if (x > 0 && x < win->settings.winW && y > 0 && y < win->settings.winH)
			{
				int distanceFromTop = y + (vis_sprites[i].spriteHeight / 2) - (win->settings.winH / 2);
				int textureOffsetY = distanceFromTop * (win->texture[4].texH / vis_sprites[i].spriteHeight);


				//int offsetY = (int)((y + (h / 2) - (win->settings.winH / 2))*H_TEX/h);
				color = *(win->texture[4].addr + ((int)(textureOffsetY * win->texture[4].texH +

				(int)(((textureOffsetX))))));

				dst = win->view.addr + (int)(y) * win->view.line_length +
				(int)(x) * (win->view.bits_per_pixel / 8);

					if (vis_sprites[i].perpDistance < win->ray.distance[(int)x])
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
    t_sprite vis_sprites[win->settings.num_sprites];
    int num_vis_sprites = 0;



	visible_sprites(win,vis_sprites,&num_vis_sprites);
	sort_sprite(vis_sprites,num_vis_sprites);

	int i = -1;


	while ( ++i < num_vis_sprites)
	{
		settings_sprite(win,vis_sprites,i);
		show_sprite(win,vis_sprites,i);
	}



    // Rendering all the visible sprites
/*    for (int i = 0; i < num_vis_sprites; i++)
	{
        t_sprite sprite = vis_sprites[i];

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
