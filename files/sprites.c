/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:24:43 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/11 23:37:46 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		visible_sprites(t_window *win, t_sprite *vis_sprites,int *num_vis_sprites)
{
	for (int i = 0; i < win->settings.num_sprites; i++)
	{
        float angleSpritePlayer = win->player.angle - atan2(win->player.posY - win->sprites[i]->sprY,
			win->sprites[i]->sprX - win->player.posX);
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
    //        win->sprites[i]->visible = 1;
            win->sprites[i]->angle = angleSpritePlayer;
			 win->sprites[i]->distance = hypot(win->sprites[i]->sprX - win->player.posX, win->sprites[i]->sprY - win->player.posY);
          //  win->sprites[i]->distance = hypot(fabs(win->sprites[i]->sprX - win->player.posX), //////////////////controlla ordine
			//							fabs(win->sprites[i]->sprY - win->player.posY));
			vis_sprites[*num_vis_sprites] = *win->sprites[i]; //////////////[0][i] oppure *
			(*num_vis_sprites)++;
        }
	//	else
	//	{
      //    win->sprites[i]->visible = 0;
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
        vis_sprites[i].perp_distance = vis_sprites[i].distance * cos(vis_sprites[i].angle);

        // Calculate the sprite projected height and width (the same, as sprites are squared)
        vis_sprites[i].sprite_height = (1 / vis_sprites[i].perp_distance) * win->draw.dist_proj_plane;
        vis_sprites[i].sprite_width = vis_sprites[i].sprite_height;

        // Sprite top Y
        vis_sprites[i].sprite_topY = (win->settings.winH / 2) - (vis_sprites[i].sprite_height / 2);
    //    vis_sprites[i].sprite_topY = (vis_sprites[i].sprite_topY < 0) ? 0 : vis_sprites[i].sprite_topY;

        // Sprite bottom Y
        vis_sprites[i].sprite_bottomY = (win->settings.winH / 2) + (vis_sprites[i].sprite_height / 2);
      //  vis_sprites[i].sprite_bottomY = (vis_sprites[i].sprite_bottomY > win->settings.winH) ? win->settings.winH : vis_sprites[i].sprite_bottomY;

        // Calculate the sprite X position in the projection plane
        vis_sprites[i].angle = atan2(vis_sprites[i].sprY - win->player.posY, vis_sprites[i].sprX - win->player.posX) + win->player.angle;
        vis_sprites[i].sprite_screen_posX = tan(vis_sprites[i].angle) * win->draw.dist_proj_plane;

        // Sprite_leftX
	//	double var;
	//	vis_sprites[i].sprite_leftX;
	//	if (win->player.diry )
        	vis_sprites[i].sprite_leftX = (win->settings.winW / 2) + vis_sprites[i].sprite_screen_posX- (vis_sprites[i].sprite_width / 2);
	//	else
		//	sprite_leftX = (win->settings.winW / 2) + sprite_screen_posX + 1;// (sprite_width / 2);

        // Sprite_rightX
        vis_sprites[i].sprite_rightX = vis_sprites[i].sprite_leftX + vis_sprites[i].sprite_width;

        // Query the width and height of the texture
       // int H_TEX = upng_get_width(textures[vis_sprites[i].texture]);
       // int 64 = upng_get_height(textures[sprite.texture]);

}

void	draw_sprite_pixel(t_window *win, t_sprite vis_sprites, int x, int y)
{
	unsigned int color;
	char *dst;

	color = *(win->textures[4].addr + ((int)(win->draw.offsetY * win->textures[4].texH +
			(int)(((win->draw.offsetX))))));
	dst = win->view.addr + (int)(y) * win->view.line_length +
	(int)(x) * (win->view.bits_per_pixel / 8);
	if (vis_sprites.perp_distance < win->ray.distance[(int)x])
	{
				if (color >= 4278190080 || color == 0)
				dst = (char *)255;
				else
					*(unsigned int*)dst = color;
	}
}

void	show_sprite(t_window *win,t_sprite *vis_sprites,int i)
{
	double x;
	int y;


	x = (vis_sprites[i].sprite_leftX);
	while (x < vis_sprites[i].sprite_rightX)
	{
		win->draw.texel_width = (win->textures[4].texW / vis_sprites[i].sprite_width);
		win->draw.offsetX = (x - vis_sprites[i].sprite_leftX) * win->draw.texel_width;
		y = vis_sprites[i].sprite_topY;
		while(y < vis_sprites[i].sprite_bottomY)
		{
			if (x > 0 && x < win->settings.winW && y > 0 && y < win->settings.winH)
			{
				win->draw.distance_from_top = y + (vis_sprites[i].sprite_height / 2) - (win->settings.winH / 2);
				win->draw.offsetY = win->draw.distance_from_top * (win->textures[4].texH / vis_sprites[i].sprite_height);
				draw_sprite_pixel(win,vis_sprites[i],x,y);
			}
			y++;
		}
		x++;
	}
}

int		sprite(t_window *win)
{
    t_sprite	vis_sprites[win->settings.num_sprites];
    int			num_vis_sprites;
	int			i;

	i = -1;
	num_vis_sprites = 0;
	visible_sprites(win,vis_sprites,&num_vis_sprites);
	sort_sprite(vis_sprites,num_vis_sprites);
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
        float perp_distance = sprite.distance * cos(sprite.angle);

        // Calculate the sprite projected height and width (the same, as sprites are squared)
        float sprite_height = (1 / perp_distance) * distprojplane;
        float sprite_width = sprite_height;

        // Sprite top Y
        float sprite_topY = (win->settings.winH / 2) - (sprite_height / 2);
        sprite_topY = (sprite_topY < 0) ? 0 : sprite_topY;

        // Sprite bottom Y
        float sprite_bottomY = (win->settings.winH / 2) + (sprite_height / 2);
        sprite_bottomY = (sprite_bottomY > win->settings.winH) ? win->settings.winH : sprite_bottomY;

        // Calculate the sprite X position in the projection plane
        float spriteAngle = atan2(sprite.sprY - win->player.posY, sprite.sprX - win->player.posX) + win->player.angle;
        float sprite_screen_posX = tan(spriteAngle) * distprojplane;

        // Sprite_leftX
	//	double var;
		float sprite_leftX;
	//	if (win->player.diry )
        	sprite_leftX = (win->settings.winW / 2) + sprite_screen_posX- (sprite_width / 2);
	//	else
		//	sprite_leftX = (win->settings.winW / 2) + sprite_screen_posX + 1;// (sprite_width / 2);

        // Sprite_rightX
        float sprite_rightX = sprite_leftX + sprite_width;

        // Query the width and height of the texture
       // int H_TEX = upng_get_width(textures[sprite.texture]);
       // int 64 = upng_get_height(textures[sprite.texture]);

        // Loop all the x values
        for (double x = sprite_leftX; x < sprite_rightX; x++)
		{
            float texel_width = (W_TEX / sprite_width);
            int textureOffsetX = (x - sprite_leftX) * texel_width;

		//	int offsetX = (x - left)*H_TEX/h;

            // Loop all the y values
            for (int y = sprite_topY; y < sprite_bottomY; y++)
			{
                if (x > 0 && x < win->settings.winW && y > 0 && y < win->settings.winH)
				{
                    int distanceFrom_top = y + (sprite_height / 2) - (win->settings.winH / 2);
                    int textureOffsetY = distanceFrom_top * (H_TEX / sprite_height);


					//int offsetY = (int)((y + (h / 2) - (win->settings.winH / 2))*H_TEX/h);
					color = *(win->textures[4].addr + ((int)(textureOffsetY*H_TEX +

					(int)(((textureOffsetX))))));

					dst = win->view.addr + (int)(y) * win->view.line_length +
					(int)(x) * (win->view.bits_per_pixel / 8);

						if (perp_distance < win->ray.distance[(int)x])
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
