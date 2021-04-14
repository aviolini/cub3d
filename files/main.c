/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:45:17 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/14 09:01:20 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_window	win;
	int			i;

	i = check_args(ac, av);
	if (!i)
	{
		printf("Error: \n%s\n(cub3D argument)\n", strerror(EINVAL));
		printf("Type: ./cub3D <map_file.cub> <\"--save\">(optional)\n");
		return (0);
	}
	init_env(&win);
	if (i == 2)
		win.settings.save = 1;
	if (!main_parsing(av[1], &win))
	{
		printf("Error: \n%s\n(map argument)\n", strerror(EINVAL));
		ft_exit(&win);
	}
	if (!main_window(&win))
	{
		printf("Error: \n%s\n(graphic server)\n", strerror(EAGAIN));
		ft_exit(&win);
	}
	return (0);
}

int	main_parsing(char *av, t_window *win)
{
	int		fd;
	int		r;
	char	*line;
	int		x;

	r = 1;
	fd = open(av, O_RDONLY);
	while (r > 0)
	{
		r = get_next_line(fd, &line);
		if (!all_params(&win->settings))
			x = parsing_params(line, &win->settings);
		else
			x = parsing_map(line, &win->settings);
		free(line);
		if (!x)
			return (0);
	}
	close(fd);
	if (r == -1 || !check_map(win, win->settings.map))
		return (0);
	return (1);
}

int	main_window(t_window *win)
{
	win->mlx = mlx_init();
	win->settings.win_def = 1;
	init_key(&win->key);
	set_right_resolution(win);
	win->win = mlx_new_window(win->mlx, win->settings.winW, \
		win->settings.winH, "Welcome");
	new_image(win, &win->view);
	if (!init_textures(win))
		return (0);
	if (!build_view(win))
		return (0);
	mlx_hook(win->win, 2, 0, press_key, win);
	mlx_hook(win->win, 3, 0, release_key, win);
	mlx_hook(win->win, 17, 0, ft_exit, win);
	mlx_loop_hook(win->mlx, key, win);
	mlx_loop(win->mlx);
	return (1);
}

void	init_env(t_window *win)
{
	win->settings.win_def = 0;
	win->settings.img_def = 0;
	win->settings.player_def = 0;
	win->settings.minimap_def = 0;
	win->settings.map = NULL;
	win->settings.winW = 0;
	win->settings.winH = 0;
	win->settings.north_texture = NULL;
	win->settings.west_texture = NULL;
	win->settings.east_texture = NULL;
	win->settings.south_texture = NULL;
	win->settings.sprite_texture = NULL;
	win->settings.floor_color = INIT_COLOR;
	win->settings.ceiling_color = INIT_COLOR;
	win->settings.eof = 0;
	win->settings.mapW = 0;
	win->settings.mapH = 0;
	win->settings.num_sprites = 0;
	win->settings.save = 0;
	win->draw.dist_proj_plane = 0;
	win->sprites = NULL;
}
