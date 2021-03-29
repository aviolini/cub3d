/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:37:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/29 10:37:21 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//int		there_is_a_wall(t_settings settings, double x, double y)
//{

//}



void	new_image(t_window *win, t_image *image)
{
	image->img = mlx_new_image(win->mlx, W_IMG, H_IMG);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
		&image->line_length, &image->endian);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char    *dst;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


void	column(t_window *win, t_image *img,int x,int orientation)
{
	double distprojplane;
	double perpdist;
	double h;
	char *dst;
	unsigned int color;
	double walltopy = 0, wallbottomy = 0;

	distprojplane = (W_IMG / 2)/tan(FOV/2);
	perpdist = win->ray.distance * (cos(win->ray.angle -win->player.angle));
	h = 1 / (perpdist) * distprojplane;
	h = (int)h;
	walltopy=H_IMG/2-h/2;
	walltopy = walltopy < 0 ? 0 : walltopy;
	wallbottomy = H_IMG / 2 + h  /2;
	wallbottomy = wallbottomy > H_IMG ? H_IMG : wallbottomy;
	//char *dst;
	int i = walltopy;
	//int z = 0;
	//	unsigned int pixel;
	//double val = wallbottomy / 64;
	while ((i) < wallbottomy)
	{

			//color = win->texture[orientation].addr[(int)((floor((double)64/h))*i + x%64)];
			color = *(int *)(win->texture[orientation].addr +
				((int)((floor(64/wallbottomy))*i)*64 +
				(int)(((x%64)))));

    		dst = img->addr + ((int)(i++) * img->line_length +
			(int)(x) * (img->bits_per_pixel / 8));
    		*(unsigned int *)dst = color;
	}
}

void	my_mlx_put_wall(t_window *win, t_image *img, int x, int color)
{
    char    *dst;
	(void) color;
//	double	i = 0;
	double distprojplane;
	double perpdist;
	double h;
	double walltopy = 0, wallbottomy = 0;

	distprojplane = (W_IMG / 2)/tan(FOV/2);
	perpdist = win->ray.distance * (cos(win->ray.angle -win->player.angle));
	h = 1 / (perpdist) * distprojplane;
	h = (int)h;
	walltopy=H_IMG/2-h/2;
	walltopy = walltopy < 0 ? 0 : walltopy;
	wallbottomy = H_IMG / 2 + h  /2;
	wallbottomy = wallbottomy > H_IMG ? H_IMG : wallbottomy;
	//char *dst;
	int i = walltopy;
	//int z = 0;

//	unsigned int pixel;
	//double val = wallbottomy / 64;
	while ((i) < wallbottomy)
	{

		//	pixel = (unsigned int)win->texture[z].addr + ((int)(i) *  win->texture[z].line_length +
		//	(int)(x) * ( win->texture[z].bits_per_pixel / 8));

    		dst = img->addr + ((int)(i++) * img->line_length +
			(int)(x) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
	}
}

int		init_textures(t_window *win)
{

	if ((!(win->texture[0].tex = mlx_xpm_file_to_image(win->mlx,win->settings.east_texture,&win->texture[0].texW,&win->texture[0].texH)))
	|| (!(win->texture[1].tex = mlx_xpm_file_to_image(win->mlx,win->settings.north_texture,&win->texture[1].texW,&win->texture[1].texH)))
	|| (!(win->texture[2].tex = mlx_xpm_file_to_image(win->mlx,win->settings.west_texture,&win->texture[2].texW,&win->texture[2].texH)))
	|| (!(win->texture[3].tex = mlx_xpm_file_to_image(win->mlx,win->settings.south_texture,&win->texture[3].texW,&win->texture[3].texH)))
	|| (!(win->texture[4].tex = mlx_xpm_file_to_image(win->mlx,win->settings.sprite_texture,&win->texture[4].texW,&win->texture[4].texH))))
			return (0);

	int i;
	int x;
	i = -1;
	x = 0;
	while (++i < 5)
		{
			if(!(win->texture[i].addr =(int *)mlx_get_data_addr(win->texture[i].tex, &win->texture[i].bits_per_pixel,
				&win->texture[i].line_length, &win->texture[i].endian)))
					return (0);
			mlx_put_image_to_window(win->mlx, win->win, win->texture[i].tex, 20 + x, 20);
			x += 65;
		}
	return (1);
}

void	view_background(t_image *view, t_settings *settings)
{
	int x;
	int y;
	int z;
	unsigned int color;

	color = settings->ceiling_color;
	y = -1;
	z = 3;

	while(--z > 0)
	{
		while(++y < (H_IMG/z) && -2 < (x = -1))
			while(++x < W_IMG)
				my_mlx_pixel_put(view,x,y,color);
		color = settings->floor_color;
		y--;
	}
}

void	set_right_resolution(t_window *win)
{
	(void)win;
	/*
	int myresx;
	int myresy;
//	mlx_get_screen_size(win->mlx, &myresx, &myresy);
	if(win->settings.win_resx > myresx)
		win->settings.win_resx = myresx;
	if(win->settings.win_resy > myresy)
		win->settings.win_resy = myresy;
*/}

int	set_distance_and_wall_orientation(t_player player, t_ray *ray)
{
	double	verh;
	double	horh;

	verh = hypot(fabs(player.posX - ray->verx), fabs(player.posY - ray->very));
	horh = hypot(fabs(player.posX - ray->horx), fabs(player.posY - ray->hory));
	if (horh <= verh)
	{
		ray->distance = horh;
		if (ray->dirY < 0)
			return (1);
		else
			return (3);
	}
	else
	{
		ray->distance = verh;
		if(ray->dirX < 0)
			return (2) ;
		else
			return (0);
	}
	return (-1);
}