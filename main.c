/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:37:37 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/05 11:42:59 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	my_mlx_pixel_put(img_data *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	my_mlx_pixel_put2(img_data *img, int x, int y, int color)
{
    char    *dst;
	int		i = -1, z = -1;

	while (++i <= img->size_pixel && -2 < (z = -1))
		while (++z <= img->size_pixel)
		{
    		dst = img->addr + ((i + y) * img->line_length +
			(x + z) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
		}
}

int		key_hook(int keycode, win_data *win)
{
	if (keycode == 53 || keycode == 65307)
	{
		mlx_destroy_image(win->mlx, win->img_s->img);
		//free array
		exit(0);
	}
	if(keycode == 126 || keycode == 65362 || keycode == 119)
		ft_keycode_up(win);
	if(keycode == 125 || keycode == 65364 || keycode == 115)
		ft_keycode_down(win);
	if(keycode == 2 || keycode == 100)
		ft_keycode_right(win);
	if (keycode == 0 || keycode == 97)
		ft_keycode_left(win);
	if(keycode == 124 || keycode == 65363)
		ft_arrow_right(win);
	if(keycode == 123 || keycode == 65361)
		ft_arrow_left(win);

	ft_bundle_ray(win);
	printf("%d\n", keycode);
	mlx_put_image_to_window(win->mlx, win->win, win->img_s->img, 20, 20);
	return 0;
}
	//RAGGIO CENTRALE
void	ft_central_ray(win_data *win)
{
	double posx, posy;
	posx = win->map_s->posx;
	posy = win->map_s->posy;
	posy -= pow(win->map_s->diry,2)* win->map_s->diry;
	posx += pow(win->map_s->dirx,2)* win->map_s->dirx;
	while (*(win->img_s->addr + ((int)posy * win->img_s->line_length +
		(int)posx * (win->img_s->bits_per_pixel / 8))) == 0)
	{
		my_mlx_pixel_put(win->img_s, posx, posy, 0x00FF0000);
		posy -= pow(win->map_s->diry,2)* win->map_s->diry;
		posx += pow(win->map_s->dirx,2)* win->map_s->dirx;
	}
}
//FASCIO DI RAGGI
void	ft_bundle_ray(win_data *win)
{
	double posx, posy;
	double t = 0;
	double angle = win->map_s->angle - M_PI/6;	//ANGOLO DI VISIONE M_PI/6 = 30GRADI
	double dirx, diry;
	while ( angle < win->map_s->angle + M_PI/6)	//+ M_PI/6 = 60GRADI
	{
		angle = win->map_s->angle - M_PI/6 + t;
		printf("angle: %f\n", angle);
		dirx = cos(angle);
		diry = sin(angle);
		posx = win->map_s->posx;
		posy = win->map_s->posy;
		posy -= diry;
		posx += dirx;
		//posy -= sin(diry)* diry;
	///	posx += cos(dirx)* dirx;
		while (*(win->img_s->addr + ((int)posy * win->img_s->line_length +
			(int)posx * (win->img_s->bits_per_pixel / 8))) == 0)
		{
			my_mlx_pixel_put(win->img_s, posx, posy, 0x00FF0000);
			posy -=  diry;
			posx +=  dirx;
			//VECCHIA FORMULA
			//posy -= pow(cos(diry),2)* diry;
			//posx += pow(sin(dirx),2)* dirx;
			//VECCHIA FORMULA
			//posy -= pow(diry,2)* diry;
			//posx += pow(dirx,2)* dirx;
		}
		t += 0.003; //AUMENTARE SE SGRANA
	}
}

int		main(void)
{
    win_data    	win;
    img_data		img;
	map_data		map;
	char			buff[5001];
	int				fd, x = 0, y = 0;
	(void) x;
	(void) y;
	unsigned int	color;

	win.img_s = &img;
	win.map_s = &map;
	map.posx = 0;
	map.posy = 0;
	map.speed = 10;
	img.size_pixel = 10;
    win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 800, 600, "Hello world!");
	//SFONDO
	//while (y++ < 1000 && -1 < (x = 0))
		//while (x++ < 1920)
			//mlx_pixel_put(win.mlx, win.win, x, y, 0x00FFFFFF);
	printf("line_lenght: %d\n", img.line_length);
	printf("line_lenght/4: %d\n", img.line_length/4);
	printf("bits_per_pixel: %d\n", img.bits_per_pixel);


	color = 255;
	printf("color: %u\n", color);
	fd = open("map_clean.cub", O_RDONLY, 0);
	read(fd, buff, 5000);
	buff[5000] = '\0';

	printf("buff\n%s\n",buff);
	map.map = ft_build_map(buff,100,14);
	img.img = mlx_new_image(win.mlx, 600, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	ft_build_image(&win);
	ft_bundle_ray(&win);
	mlx_put_image_to_window(win.mlx, win.win, img.img, 20, 20);
	//mlx_key_hook(win.win, key_hook, &win); //NON FUNZIONA CON TASTO TENUTO PREMUTO
	mlx_hook(win.win, 2, 1L<<0, key_hook, &win);
	//mlx_loop_hook(win.mlx, key_hook, &win);  //FUNZIONA SENZA PREMERE TASTI
    mlx_loop(win.mlx);
}
