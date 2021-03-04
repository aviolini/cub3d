/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:00:35 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/04 15:12:58 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}
void	ft_destroy_img(win_data *win)
{
	mlx_destroy_image(win->mlx, win->img_s->img); //sosituire con clean?
	win->img_s->img = mlx_new_image(win->mlx, 600, 480);
	win->img_s->addr = mlx_get_data_addr(win->img_s->img,
		&win->img_s->bits_per_pixel, &win->img_s->line_length, &win->img_s->endian);
}
char	**ft_build_map (char *buff, int x, int y)
{
	char **map;
	int j = 0, i = 0, z = 0;
	map = (char **)malloc(sizeof(char *) * (y + 1));
	while (j < y)
	{
		map[j] = (char *)malloc(sizeof(char) * (x + 1));
		while (buff[i] != '\n')
		{
			if (buff[i] == ' ')
				map[j][z] = ' ';
			else if (buff[i] == '1')
		 		map[j][z] = '1';
			else if (buff[i] == '0')
				map[j][z] = '0';
			else if (buff[i] == '2')
				map[j][z] = '2';
			else if (buff[i] == 'N')
				map[j][z] = 'N';
			else if (buff[i] == 'S')
				map[j][z] = 'S';
			else if (buff[i] == 'E')
				map[j][z] = 'E';
			else if (buff[i] == 'W')
				map[j][z] = 'W';
			i++;
			z++;
		}
		map[j][z++] = '\0';
		i++;
		j++;
		z = 0;
	}
	map[y] = NULL;
		j = 0;
	while ( j < y)
		printf("map%s\n",map[j++]);
	return map;
}
void	ft_build_image(win_data *win, int a)
{
	int j = 0;
	int z = 0;
	int x = win->img_s->size_pixel;
	int y = win->img_s->size_pixel;

	while (win->map_s->map[j])
	{

		while ( win->map_s->map[j][z] != '\0')
		{
			if (win->map_s->map[j][z] == '1')
    			my_mlx_pixel_put2(win->img_s, x, y, 255);
			if (win->map_s->map[j][z] == '2')
		    	my_mlx_pixel_put2(win->img_s, x, y, 0x0000FFFF);
			if (win->map_s->map[j][z] == 'N' && a == 1)
			{
				win->map_s->posx = x;
				win->map_s->posy = y;
				win->map_s->angle = M_PI/2;
				my_mlx_pixel_put(win->img_s, x, y, 0x00FFFFFF);
			}
			if (win->map_s->map[j][z] == 'S' && a == 1)
			{
				win->map_s->posx = x;
				win->map_s->posy = y;
				win->map_s->angle = 3*M_PI/2;
				my_mlx_pixel_put(win->img_s, x, y, 0x00FFFFFF);
			}
			if (win->map_s->map[j][z] == 'E' && a == 1)
			{
				win->map_s->posx = x;
				win->map_s->posy = y;
				win->map_s->angle = M_PI;
				my_mlx_pixel_put(win->img_s, x, y, 0x00FFFFFF);
			}
			if (win->map_s->map[j][z] == 'W' && a == 1)
			{
				win->map_s->posx = x;
				win->map_s->posy = y;
				win->map_s->angle = 0;
				my_mlx_pixel_put(win->img_s, x, y, 0x00FFFFFF);
			}
			x = x + win->img_s->size_pixel;
			z++;
		}
		j++;
		z = 0;
		win->map_s->dirx = cos(win->map_s->angle);
		win->map_s->diry = sin(win->map_s->angle);
		x = win->img_s->size_pixel;
		y = y + win->img_s->size_pixel;
	}
}
void	ft_ray_coordinate(win_data *win)
{
	int posx, posy;
	double doubx, douby;
	double posdirx = -1;
	double posdiry = 0;
	posx = win->map_s->posx;
	posy = win->map_s->posy;
	doubx = posx;
	douby = posy;

	int i = 0;
while(i++ < 100)
	{
		my_mlx_pixel_put(win->img_s, doubx, douby, 0x00FF0000);
		if (posdirx ==  -1 && posdiry == 0)
		{
			douby++;
			doubx--;
		}
		if (posdirx == 1 && posdiry == 0)
		{
			doubx++;
			douby++;
		}
		if (posdirx ==  0 && posdiry == -1)
		{
			douby--;
			doubx--;
		}
		if (posdirx == 0 && posdiry == 1)
		{
			doubx++;
			douby++;
		}

	}
	i = 0;
	posx = win->map_s->posx;
	posy = win->map_s->posy;
	doubx = posx;
	douby = posy;
	while(i++ < 100)
		{
			my_mlx_pixel_put(win->img_s, doubx, douby, 0x00FF0000);
			if (posdirx ==  -1 && posdiry == 0)
			{
				douby--;
				doubx--;
			}
			if (posdirx == 1 && posdiry == 0)
			{
				douby--;
				doubx++;
			}
			if (posdirx ==  0 && posdiry == -1)
			{
				douby--;
				doubx++;
			}
			if (posdirx == 0 && posdiry == 1)
			{
				doubx--;
				douby++;
			}
		}
}
