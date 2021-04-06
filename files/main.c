/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:45:17 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/06 12:07:50 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		main(int ac, char **av)
{
	t_window win;
	int i;
	i = 0;
	if (!(i = check_args(ac,av)))
		return (0);
	else if (i == 2)
		printf("ok args\nsalvare l'immagine bmp non stampare\n"); //CONTINUA IL PROGRAMMA
	init_settings(&win.settings);
	if (!main_parsing(av[1], &win))
	{
		printf("Error: \n%s\n(argument of map)\n", strerror(EINVAL));
		ft_exit(&win);
	}
	if(!main_window(&win))
	{
		printf("Error: \n%s\n(graphic server)\n", strerror(EAGAIN));
		ft_exit(&win);
	}
	return (0);
}

int		main_parsing(char *av, t_window *win)
{
	int fd;
	int r;
	char *line;

	r = 1;
	fd = open(av, O_RDONLY);
	while (r > 0)
	{
		r = get_next_line(fd,&line);
		if (!all_params(&win->settings))
		{
			if (!parsing_params(line,&win->settings))
			{
							free(line);
				return (0);

			}
		}
		else
 			if (!parsing_map(line,&win->settings))
			{
				free(line);
					return (0);
			}
		free(line);
	}
	close(fd);
	if (r == -1 || !check_map(win, win->settings.map, win->settings.mapH, win->settings.mapW))
		return(0);
	return (1);
}

int		main_window(t_window *win)
{
	win->mlx = mlx_init();
	win->settings.win_def = 1;
	init_key(&win->key);

//	set_right_resolution(win);
	win->win = mlx_new_window(win->mlx,win->settings.winW*2-400,////////////////////////////
		win->settings.winH, "Welcome");
	if (!init_textures(win))
		return (0);
	if (!build_view(win))
		return (0);
	print_settings(win->settings);
	print_player(win->player);
/* ////PER UN MOVIMENTO PIU FLUIDO
	mlx_hook(win->win, 2, 0, press_key, win);
	mlx_hook(win->win, 3, 0, release_key, win);
	mlx_hook(win->win, 17, 0, ft_exit, win);
	mlx_loop_hook(win->mlx, key, win);
	mlx_loop(win->mlx);
*/ /////////////////////////////

	mlx_hook(win->win, 2, 1L<<0, key_hook, win);
//	mlx_hook(win->win, 2, 17<<0, ft_exit, win);
	mlx_loop(win->mlx);
	return (1);
}

void	init_settings(t_settings *settings)
{
	settings->win_def = 0;
	settings->map = NULL;
	settings->winW = 0;
	settings->winH = 0;
	settings->north_texture = NULL;
	settings->west_texture = NULL;
	settings->east_texture = NULL;
	settings->south_texture = NULL;
	settings->sprite_texture = NULL;
	settings->floor_color = 0;
	settings->ceiling_color = 0;
	settings->eof = 0;
	settings->mapW = 0;
	settings->mapH = 0;
	settings->num_of_sprite = 0;
}
