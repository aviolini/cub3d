#include "cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void            my_mlx_pixel_put(img_data *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void            my_mlx_pixel_put2(img_data *img, int x, int y, int color)
{
    char    *dst;
	int		i = -1, z = -1;

	while (++i <= img->size_pixel && -2 < (z = -1))
		while (++z <= img->size_pixel)
		{
    		dst = img->addr + ((i + y) * img->line_length + (x + z) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
		}
}

int		key_hook(int keycode, win_data *win)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 124)
	{
		my_mlx_pixel_put2(win->img_s, win->img_s->xn, win->img_s->yn, 0x00FF0000);
		mlx_put_image_to_window(win->mlx, win->win, win->img_s->img, 20, 20);
	}
	printf("%d\n", keycode);
	return 0;
}

int             main(void)
{
    win_data    	win;
    img_data		img;
	char			buff[5001];
	char			map[14][1000];
	int				fd, x = 0, y = 0, r = 0, i = 0, j = 0,z = 0;
	unsigned int	color;
	win.img_s = &img;
    win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 800, 600, "Hello world!");
	img.img = mlx_new_image(win.mlx, 600, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	while (y++ < 1000 && -1 < (x = 0))
		while (x++ < 1920)
			mlx_pixel_put(win.mlx, win.win, x, y, 0x00FFFFFF);
	printf("line_lenght: %d\n", img.line_length);
	printf("line_lenght/4: %d\n", img.line_length/4);
	printf("bits_per_pixel: %d\n", img.bits_per_pixel);

	img.size_pixel = 10;
	color = 255;
	printf("color: %u\n", color);
	y = -1;
	fd = open("map_clean.cub", O_RDONLY, 0);
	r = read(fd, buff, 5000);
	buff[5000] = '\0';
	//map[14][0] = NULL;
	printf("buff\n%s\n",buff);
	while (j < 14)
	{
		while (buff[i] != '\n')
		{
			if (buff[i] == ' ')
				map[j][z] = ' ';
				//i++;
			else if (buff[i] == '1')
		 		map[j][z] = '1';
			else if (buff[i] == '0')
				map[j][z] = '0';
			else if (buff[i] == '2')
				map[j][z] = '2';
			else if (buff[i] == 'N')
				map[j][z] = 'N';
			i++;
			z++;
		}
		map[j][z++] = '\0';
		i++;
		j++;
		z = 0;
	}
	j = 0;

	while ( j < 14)
		printf("map%s\n",map[j++]);

		j = 0;
		z = 0;
		x = img.size_pixel;
		y = img.size_pixel;
	//}
	while (j < 14)
	{
		while ( map[j][z] != '\0')
		{
			if (map[j][z] == '1')
    			my_mlx_pixel_put2(&img, x, y, color);
			if (map[j][z] == 'N')
			{
				img.xn = x;
				img.yn = y;
	    		my_mlx_pixel_put2(&img, x, y, 0x00FFFFFF);
			}
			if (map[j][z] == '2')
		    	my_mlx_pixel_put2(&img, x, y, 0x0000FFFF);
			x = x + img.size_pixel;
			z++;
			//printf("color: %u\n", color);
		}
		j++;
		z = 0;
		x = img.size_pixel;
		y = y + img.size_pixel;
	}
    mlx_put_image_to_window(win.mlx, win.win, img.img, 20, 20);
	mlx_key_hook(win.win, key_hook, &win);
    mlx_loop(win.mlx);
}
