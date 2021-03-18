/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:45:17 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/18 11:27:14 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	win_data win;
	int i;
	i = 0;
	if (!(i = check_args(ac,av)))
		return (0);
	else if (i == 2)
		printf("ok args\nsalvare l'immagine bmp non stampare\n"); //CONTINUA IL PROGRAMMA
	init_settings(&win.settings);
	if (!parsing_file(av[1], &win.settings))
		printf("Error\nError in parsing map\nProbably wrong params\n");
	print_settings(win.settings);
	if(!main_window(&win))
		printf("Error\nError in graphic server\n");
	return (0);
}

int		parsing_file(char *av, sett_data *settings)
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
 			if (!parsing_map(line,&settings->map, &settings->eof))
					return (0);
	//	free(line);
	}
	if ( r == -1)
		return (0);
	if (!check_map(settings->map))
		return(0);
	return (1);
}


void		print_settings(sett_data settings)
{
	printf("------settings------------------------\n");
	//int i = 0;
	//printf("*map: %i\n",*(settings->map));
	printf("w_win: %i\n",settings.win_resx);
	printf("h_win: %i\n",settings.win_resy);
	printf("no_te: %s\n",settings.north_texture);
	printf("we_te: %s\n",settings.west_texture);
	printf("ea_te: %s\n",settings.east_texture);
	printf("so_te: %s\n",settings.south_texture);
	printf("sp_te: %s\n",settings.sprite_texture);
	printf("flo_col: %i\n",settings.floor_color);
	printf("cei_col: %i\n",settings.ceiling_color);
	printf("eof: %i\n",settings.eof);
	//while ((settings->map)[i])
	//	printf("mapp: %s\n",(settings->map)[i++]);
	while (*(settings.map))
	{
		printf("map: %s-\n",*(settings.map));
		(settings.map)++;
	}
	printf("-----------------------------------\n");
}

void		init_settings(sett_data *settings)
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
}
