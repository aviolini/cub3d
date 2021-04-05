/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/05 22:15:50 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		build_view(t_window *win)
{

//	mlx_clear_window(win->mlx,win->win);
	new_image(win, &win->world);
	new_image(win, &win->view);
	if(!build_world(&win->world, win->settings.map, &win->player))
		return (0);
	view_background(&win->view, &win->settings);

	//int c = 0;
	//win->ray = (t_ray *)malloc(sizeof(t_ray)*win->settings.winW)
	//while (c < win->settings.winX)
	//	{
	//		win->ray[c]=(t_ray *)malloc(sizeof(t_ray))
	//	}

	image(win);
	miniray(win);
	sprite(win);
	free(win->ray.distance);
	mlx_put_image_to_window(win->mlx, win->win, win->world.img, 05, 20);
	mlx_put_image_to_window(win->mlx, win->win, win->view.img, 700, 0);

mlx_destroy_image(win->mlx, win->world.img);
	mlx_destroy_image(win->mlx, win->view.img);

	return (1);
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


int		sprite(t_window *win)
{
    t_sprite visibleSprites[win->settings.num_of_sprite];
    int numVisibleSprites = 0;
	unsigned int color;
	char *dst;




    // Find sprites that are visible (inside the FOV)
    for (int i = 0; i < win->settings.num_of_sprite; i++)
	{
        float angleSpritePlayer = win->player.angle + atan2(win->sprite[i]->sprY - win->player.posY,
			win->sprite[i]->sprX - win->player.posX);

        // Make sure the angle is always between 0 and 180 degrees
        if (angleSpritePlayer > M_PI)
            angleSpritePlayer -= M_PI * 2;
      //  if (angleSpritePlayer < -M_PI)
        //    angleSpritePlayer += M_PI * 2;
       // angleSpritePlayer = fabs(angleSpritePlayer);

        // If sprite angle is less than half the FOV plus a small margin
        const float EPSILON = 0.2;
		if (angleSpritePlayer < (FOV/2) + EPSILON)
		{
            win->sprite[i]->visible = 1;
            win->sprite[i]->angle = angleSpritePlayer;
			 win->sprite[i]->distance = distanceBetweenPoints(win->sprite[i]->sprX, win->sprite[i]->sprY, win->player.posX, win->player.posY);
          //  win->sprite[i]->distance = hypot(fabs(win->sprite[i]->sprX - win->player.posX), //////////////////controlla ordine
			//							fabs(win->sprite[i]->sprY - win->player.posY));
			visibleSprites[numVisibleSprites] = *win->sprite[i]; //////////////[0][i] oppure *
			numVisibleSprites++;
        }
		else
		{
            win->sprite[i]->visible = 0;
        }
    }

	// Sort sprites by distance using a naive bubble-sort algorithm
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

	double distprojplane = (win->settings.winW / 2)/tan(FOV/2);

    // Rendering all the visible sprites
    for (int i = 0; i < numVisibleSprites; i++)
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
	return (1);
}







/*
int		sprite(t_window *win)
{
	double max;
	int c;
	t_sprite *temp;
	max = 0;
	c = 0;
	double angle;

	//angle = remainder(win->win->player.angle, 2*M_PI);
	angle = remainder(win->player.angle,M_PI);
	if (angle < 0)
		angle = 2*M_PI + angle;


	t_sprite visibleSprites[win->settings.num_of_sprite];
    int numVisibleSprites = 0;

	for (int i = 0; i < win->settings.num_of_sprite; i++)
	{
		float angleSpritePlayer = angle - atan2(win->sprite[i]->sprY - win->player.posY,
			win->sprite[i]->sprX - win->player.posX);

		// Make sure the angle is always between 0 and 180 degrees
		if (angleSpritePlayer > M_PI)
			angleSpritePlayer -= M_PI*2;
		if (angleSpritePlayer < -M_PI)
			angleSpritePlayer += M_PI*2;
		angleSpritePlayer = fabs(angleSpritePlayer);

		// If sprite angle is less than half the FOV plus a small margin
		const float EPSILON = 0.2;
		if (angleSpritePlayer < (FOV / 2) + EPSILON)
		{
			win->sprite[i]->visible = 1;
			win->sprite[i]->angle = angleSpritePlayer;
			win->sprite[i]->distance = hypot(win->sprite[i]->sprY - win->player.posY,
				win->sprite[i]->sprX - win->player.posX);
			visibleSprites[numVisibleSprites] = *win->sprite[i];
			numVisibleSprites++;
		}
		else
		{
			win->sprite[i]->visible = 0;
		}
	}



	// Sort sprites by distance using a naive bubble-sort algorithm
	for (int i = 0; i < numVisibleSprites - 1; i++) {
		for (int j = i + 1; j < numVisibleSprites; j++) {
			if (visibleSprites[i].distance < visibleSprites[j].distance) {
				sprite_t temp = visibleSprites[i];
				visibleSprites[i] = visibleSprites[j];
				visibleSprites[j] = temp;
			}
		}
	}



while(c<numVisibleSprites)// && win->sprite[c]->distance > 0)
{
//		printf("co\n\n");
	//c = 0;
	if (visibleSprites[c].distance < visibleSprites[c + 1].distance)
	{
//			printf("ciao\n\n");
		temp = 	&visibleSprites[c + 1];
		visibleSprites[c + 1] = visibleSprites[c];
		visibleSprites[c] = *temp;
		c = -1;
	}
	c++;
}

c = 0;
double h;
char *dst;
unsigned int color;
double distprojplane;
double walltopy = 0, wallbottomy = 0;

distprojplane = (win->settings.winW / 2)/tan(FOV/2);

	// Rendering all the visible sprites
	for (int i = 0; i < numVisibleSprites; i++)
	{
		t_sprite sprite = visibleSprites[i];

		// Calculate the perpendicular distance of the sprite to prevent fish-eye effect
		float perpDistance = sprite.distance * cos(sprite.angle);

		// Calculate the sprite projected height and width (the same, as sprites are squared)
		float h = (1 / perpDistance) * distprojplane;





//	while(c<win->settings.num_of_sprite && win->sprite[c]->distance > 0)
//	{
		//h = H_TEX / ;
		walltopy=win->settings.winH/2-h/2;
		walltopy = walltopy < 0 ? 0 : walltopy;
		wallbottomy = win->settings.winH / 2 + h  /2;
		wallbottomy = wallbottomy > win->settings.winH ? win->settings.winH : wallbottomy;
		//char *dst;
		//////////////////////////SOSTITUZIONE
		//int u = 0;					//ORIGINALE
		//while (H_TEX/h*u++ < H_TEX-1)		//ORIGINALE



		float spriteAngle = atan2(sprite.sprY - win->player.posY, sprite.sprX - win->player.posX) - (angle);
		float spriteScreenPosX = tan(spriteAngle) * distprojplane;
	int u = 0;
	double left = (win->settings.winH / 2) + spriteScreenPosX - h/2;
	double right = left + h;
	int y = walltopy;
		int x = left;
		int p = 0;
		while (x++ < (int)right)
		{

			int offsetX = (x - left)*H_TEX/h;
		//	printf("offsetX : %d \n",offsetX);
		//	printf("X : %d \n",x);
			 y = walltopy;
			while ((y) < wallbottomy)
			{
		//RIMETTERE	//if(x > 0 && x < win->settings.winW && y > 0 && y < win->settings.winH)
			//{
			//	if (win->sprite[c]->i + p < win->settings.winW) //FIX DEL LIMITE DELLA SPR_TEXT VERSO DX ->
			//	{
					int offsetY = (int)((y + (h / 2) - (win->settings.winH / 2))*H_TEX/h);
					color = *(win->texture[4].addr + ((int)(offsetY*H_TEX +

					(int)(((offsetX))))));

					dst = win->view.addr + (int)(y) * win->view.line_length +
					(int)(spriteScreenPosX+p) * (win->view.bits_per_pixel / 8);

		//	if (win->sprite[c]->distance < win->ray.distance[win->sprite[c]->i])
		//	{
		//				if (color >= 4278190080 || color == 0)
		//				dst = (char *)255;
		//				else
							*(unsigned int*)dst = color;
		//	}
			//}
				y++;
			}
			p++;
		//	u++;
		}
		//win->sprite[c]->distance = 0;
	//	win->sprite[c]->sprX = 0;
	//	win->sprite[c]->sprY = 0;
	//	win->sprite[c]->distance = 0;
		c++;

	}
	return (1);
}*/

int		image(t_window *win)
{
	win->ray.angle = win->player.angle + FOV/2;
	int i = -1;

	//int color;
	int orientation;


	win->ray.distance = (double *)malloc(sizeof(double) * win->settings.winW);
	while (++i < win->settings.winW)
	{

		win->ray.dirX = cos(win->ray.angle);
		win->ray.dirY = -sin(win->ray.angle);
		check_hor_intersection(win,&win->settings, win->player, &win->ray,i);
		check_ver_intersection(win,&win->settings, win->player, &win->ray,i);




		orientation = set_distance_and_wall_orientation(win->player,&win->ray,i);
	//	color = set_wall_color(orientation);
	//	my_mlx_put_wall(win, &win->view, x, color);
		column(win, &win->view,i,orientation);

	//	sprite
win->ray.angle -= FOV/win->settings.winW;
	}
/*	int z = 0;
	while (win->sprite[z])
		{
			printf("X : %f\t Y: %f\n",win->sprite[z]->sprX, win->sprite[z]->sprY);
			printf("distance : %f\n",win->sprite[z]->distance);
			z++;
		}

		printf("\n\n");

		 z = 0;
		while (win->sprite[z])
			{
				printf("X : %f\t Y: %f\n",win->sprite[z]->sprX, win->sprite[z]->sprY);
				printf("distance : %f\n",win->sprite[z]->distance);
				z++;
			}
*/	return (1);
}

void	check_hor_intersection(t_window *win, t_settings *settings, t_player player, t_ray *ray,int i)
{
	//TOGLIERE WIN DATA WIN , TOGLIERE MY_MLX_PIXEL_PUT
	int		roundy;
	double	horx;
	double	hory;

	if(ray->dirY < 0)
	{
		roundy = 0;
		ray->value_y = 1;
	}
	else
	//if (ray->dirY > 0)
	{
		roundy = 1;
		ray->value_y = -1;
	}

	hory = floor(player.posY) + roundy;
	horx = player.posX + (fabs((player.posY) -(hory))
				/ (ray->value_y * tan(ray->angle)));
	while (floor(horx) >= 0 && floor(horx) < settings->mapW)
	{

		if (settings->map[(int)floor((hory) + (roundy - 1))][(int)floor(horx)] == '1')
		{
			my_mlx_pixel_put(&win->world, horx*SCALE, hory*SCALE, WHITE);
			ray->horx = horx;
			ray->hory = hory;
			return ;
		}
		if (settings->map[(int)floor(hory)][(int)floor(horx)] == '2')
		{
			my_mlx_pixel_put(&win->world, horx*SCALE, hory*SCALE, GREEN);
		//	sprite_intersections(win, win->sprite, horx, hory,i);
		}
		//my_mlx_pixel_put(&win->world, horx*SCALE, hory*SCALE, WHITE);
		hory -= ray->value_y;
		horx += ray->value_y/tan(ray->angle);
	}
	ray->horx = MY_MAX_LIMIT;
	ray->hory = MY_MAX_LIMIT;
}

void	check_ver_intersection(t_window *win,t_settings *settings, t_player player, t_ray *ray,int i)
{
	int		roundx;
	double	verx;
	double	very;

	if(ray->dirX < 0)
	{
		roundx = 0;
		ray->value_x = 1;
	}
	//if (ray->dirX > 0)
	else
	{
		roundx = 1;
		ray->value_x = -1;
	}
		verx = floor(player.posX / 1) * 1 + roundx;
		very = player.posY + (fabs(player.posX - verx))
		* (ray->value_x * tan(ray->angle));
		while((floor(very) > 0 && floor(very) < settings->mapH))
		{

			if (settings->map[(int)floor(very)][(int)floor(verx + (roundx - 1) )] == '1')
			{
				my_mlx_pixel_put(&win->world, verx*SCALE, very*SCALE, YELLOW);
				ray->verx = verx;
				ray->very = very;
				return ;
			}
			if (settings->map[(int)floor(very)][(int)floor(verx)] == '2')
			{
			//	sprite_intersections(win, win->sprite, verx, very,i);
				my_mlx_pixel_put(&win->world, verx*SCALE, very*SCALE, BLUE);
			}
			verx -= ray->value_x ;
			very += ray->value_x *tan(ray->angle);
		 }
	ray->verx = MY_MAX_LIMIT;
	ray->very = MY_MAX_LIMIT;
}
