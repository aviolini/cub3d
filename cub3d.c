/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:45:17 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/19 20:02:01 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int ac, char **av)
{
	win_data win;
	int i;
	i = 0;
	if (!(i = check_args(ac,av)))
		return (0);
	else if (i == 2)
		printf("ok args\nsalvare l'immagine bmp non stampare\n"); //CONTINUA IL PROGRAMMA
	init_settings(&win.settings);
	if (!main_parsing(av[1], &win.settings, &win.player))
		printf("Error\nError in parsing map\nProbably wrong params\n");
	print_settings(win.settings);
	if(!main_window(&win))
		printf("Error\nError in graphic server\n");
	return (0);
}

int		main_parsing(char *av, sett_data *settings, pl_data *player)
{
	int fd;
	int r;
	char *line;

	r = 1;
	fd = open(av, O_RDONLY);
	while (r > 0)
	{
		line = NULL;
		r = get_next_line(fd,&line);
		if (!all_params(settings))
		{
			if (!parsing_params(line,settings))
				return (0);
		}
		else
 			if (!parsing_map(line,settings))
					return (0);
		free(line);
	}
	if ( r == -1)
		return (0);
	if (!check_map(settings->map, settings->mapy, settings->mapx,player))
		return(0);
	return (1);
}

int		main_window(win_data *win)
{
	win->mlx = mlx_init();
//	set_right_resolution(win);
	win->win = mlx_new_window(win->mlx,win->settings.win_resx,
		win->settings.win_resy, "Welcome");
	build_view(win);
	print_player(win->player);
	mlx_hook(win->win, 2, 1L<<0, key_hook, win);
//	mlx_hook(win->win, 2, 17, ft_exit, win);
	mlx_loop(win->mlx);
	return (1);
}

void	init_settings(sett_data *settings)
{
	settings->map = NULL;
	settings->win_resx = 0;
	settings->win_resy = 0;
	settings->north_texture = NULL;
	settings->west_texture = NULL;
	settings->east_texture = NULL;
	settings->south_texture = NULL;
	settings->sprite_texture = NULL;
	settings->floor_color = 0;
	settings->ceiling_color = 0;
	settings->eof = 0;
	settings->mapx = 0;
	settings->mapy = 0;
}
