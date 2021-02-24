#include <mlx.h>
#include <stdio.h>

typedef struct	s_data
{
	void		*mlx;
	void		*win;
}				t_data;

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		key_hook(int keycode, t_data *s )
{
	(void)s;
	printf("%d\n", keycode);
	return 0;
}

int     main(void)
{
	t_data	s;
	int x = 0;

	int z = create_trgb(0,0,1,0);

	printf("colour:%i\n",z);
    s.mlx = mlx_init();
    s.win = mlx_new_window(s.mlx, 100, 100, "Hello world!");
	while (x++ < 50)
		mlx_pixel_put(s.mlx, s.win, x,50, 0x00FFFFFF);
	mlx_key_hook(s.win, key_hook, &s);
	mlx_loop(s.mlx);


}
