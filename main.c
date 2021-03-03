#include "cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void ft_destroy_img(win_data *win)
{
	mlx_destroy_image(win->mlx, win->img_s->img); //sosituire con clean?
	win->img_s->img = mlx_new_image(win->mlx, 600, 480);
	win->img_s->addr = mlx_get_data_addr(win->img_s->img,
		&win->img_s->bits_per_pixel, &win->img_s->line_length, &win->img_s->endian);
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
    		dst = img->addr + ((i + y) * img->line_length +
			(x + z) * (img->bits_per_pixel / 8));
    		*(unsigned int*)dst = color;
		}
}

char **ft_build_map (char *buff, int x, int y)
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

void	ft_build_image(win_data *win)
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
			if (win->map_s->map[j][z] == 'N')
			{
				win->map_s->posx = x;
				win->map_s->posy = y;
				my_mlx_pixel_put2(win->img_s, x, y, 0x00FFFFFF);
			}
			if (win->map_s->map[j][z] == '2')
		    	my_mlx_pixel_put2(win->img_s, x, y, 0x0000FFFF);
			x = x + win->img_s->size_pixel;
			z++;

		}


		j++;
		z = 0;
		x = win->img_s->size_pixel;
		y = y + win->img_s->size_pixel;
	}
//	mlx_put_image_to_window(win->mlx, win->win, win->img_s->img, 20, 20);

}

int		key_hook(int keycode, win_data *win)
{
//	char dst[5000];
	if (keycode == 53 || keycode == 65307)
	{
		mlx_destroy_image(win->mlx, win->img_s->img);
		//free array
		exit(0);
	}
	if (keycode == 123 || keycode == 65361)
		ft_keycode_left(win);
	if(keycode == 126|| keycode == 65362)
		ft_keycode_up(win);
	if(keycode == 124|| keycode == 65363)
		ft_keycode_right(win);
	if(keycode == 125|| keycode == 65364)
		ft_keycode_down(win);


	//ft_build_image(win);

	// RAGGIO
//	win->map_s->posy--;
//	win->map_s->posx = win->map_s->posx + (win->img_s->size_pixel / 2);
//	while (*(win->img_s->addr + (win->map_s->posy * win->img_s->line_length +
//		win->map_s->posx * (win->img_s->bits_per_pixel / 8))) == 0)
//		{
//			my_mlx_pixel_put(win->img_s, win->map_s->posx, win->map_s->posy, 0x00FF0000);
//			win->map_s->posy--;
//		}

	mlx_put_image_to_window(win->mlx, win->win, win->img_s->img, 20, 20);
	printf("%d\n", keycode);
	return 0;
}

int             main(void)
{
    win_data    	win;
    img_data		img;
	map_data		map;
	char			buff[5001];
	int				fd, x = 0, y = 0, r = 0;
	(void) x;
	(void) y;
	unsigned int	color;

	win.img_s = &img;
	win.map_s = &map;
    win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 800, 600, "Hello world!");

	//while (y++ < 1000 && -1 < (x = 0))
		//while (x++ < 1920)
			//mlx_pixel_put(win.mlx, win.win, x, y, 0x00FFFFFF);
	printf("line_lenght: %d\n", img.line_length);
	printf("line_lenght/4: %d\n", img.line_length/4);
	printf("bits_per_pixel: %d\n", img.bits_per_pixel);

	img.size_pixel = 10;
	color = 255;
	printf("color: %u\n", color);
	fd = open("map_clean.cub", O_RDONLY, 0);
	r = read(fd, buff, 5000);
	buff[5000] = '\0';

	printf("buff\n%s\n",buff);
	map.map = ft_build_map(buff,100,14);
	img.img = mlx_new_image(win.mlx, 600, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	ft_build_image(&win);
	mlx_put_image_to_window(win.mlx, win.win, img.img, 20, 20);
	//mlx_key_hook(win.win, key_hook, &win); //NON FUNZIONA CON TASTO TENUTO PREMUTO
	mlx_hook(win.win, 2, 1L<<0, key_hook, &win);
	//mlx_loop_hook(win.mlx, key_hook, &win);  //FUNZIONA SENZA PREMERE TASTI
    mlx_loop(win.mlx);
}
