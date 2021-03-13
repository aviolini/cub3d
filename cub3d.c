/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:45:17 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/13 12:18:56 by aviolini         ###   ########.fr       */
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
	print_strutt(&win.settings);
	if (!parsing_map(av[1], &win.settings)) //SE TORNA 0 = ERRORE
		printf("Error\nError in parsing map\nProbably wrong params");
	else
		printf("ok");

	return (0);
}
void		print_strutt(sett_data *settings)
{
	printf("w_win: %i\n",settings->width_win);
	printf("h_win: %i\n",settings->height_win);
	printf("no_text: %s\n",settings->north_texture);]
	printf("we_te: %s\n",settings->west_texture);
	printf("ea_te: %s\n",settings->east_texture);
	printf("so_te: %s\n",settings->south_texture);
	printf("sp_te: %s\n",settings->sprite_texture);
	printf("flo_col: %i\n",settings->floor_color);
	printf("cei_col: %i\n",settings->ceiling_color);
}
void		init_settings(sett_data *settings)
{
	*(settings->map) = NULL;
	settings->width_win = 0;
	settings->heigth_win = 0;
	settings->north_texture = NULL;
	settings->west_texture = NULL;
	settings->east_texture = NULL;
	settings->south_texture = NULL;
	settings->sprite_texture = NULL;
	settings->floor_color = 0;
	settings->ceiling_color = 0;
}
