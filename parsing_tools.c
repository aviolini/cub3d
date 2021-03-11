/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:34:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/11 19:49:00 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_resolution(char *line, sett_data *settings, int i)
{
	//1.IMPOSTARE LA RISOLUZIONE IN AUTOMATICO SE NON E SUPPORTATA
	//2.IMPOSTARE LA PROTEZIONE SULLA RICERCA, SE ARRIVA A FINE STRINGA O
	//SE NON TROVA IL SECONDO PARAMETRO O SE NON TROVA SOLO NUMERI
	//OTTENERE LA RISOLUZIONE:
	// int mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
	if (settings->width_win || settings->height_win)
		return (0);
	i++;
	while(line[i] == ' ')
		i++;
	while(is_digit(line[i]))
		settings->width_win = settings->width_win * 10 + (line[i++] - 48);
	while(line[i] == ' ')
		i++;
	while(is_digit(line[i]))
		settings->height_win = settings->height_win * 10 + (line[i++] - 48);
	return (1);
}

int		path_textures(char *line, char *texture, int i)
{
	int c;
	int z;

	z = 0;
	c = 0;
	i += 2;
	if (texture)
		return (0);
	while (line[i] == ' ')
		i++;
	z = i;
	while (line[i] && line[i] != ' ')
	{
		i++;
		c++;
	}
	if (!(texture = (char *)malloc(sizeof(char) * (c + 1))))
		return (-1);
	c = 0;
	while (line[z] && line[z] != ' ')
			texture[c++] = line[z++];
	texture[c] = '\0';
	return (1);
}

int		parsing_map(char *av, sett_data *settings)
{
	int fd;
	int i;
	int r;
	int params;
	char *line;

	params = 0;
	line = NULL;
	fd = open(av, O_RDONLY);
	while (r = get_next_line(fd,&line) > 0)
	{
		if (params < 8)
		{
			if (line[0] != '\0')
			{
				if ((i = check_params(line,settings)) == -1)
						return (0)
				params =+i;
			}
		}
		else	//DA PERFERZIONARE////////////////////////////////
			if (line[0] != '\0' && *!settings->map)
			{
 				if (!build_map(line,settings) == -1)
					return (0);
			}
			if (line [0] == '\0' && *settings->map)
				return (0);
	}
	if ( r == -1)
		return (0);
	return (1);
}

int		set_color(char *line, int *color)
{
	int r;
	int g;
	int b;

	i++;
	if (color)
		return (0);
	while (line[i] || line[i] == ' ')
		i++;
	r = find_color(line,i);
	while (is_digit(line[i]) || line[i] == ',' || line[i] == ' ')
		i++;
	g = find_color(line, i);
	while (is_digit(line[i]))
		i++;
	b = find_color(line, i);
	color = (r << 16 | g << 8 | b);
	return (1);
}

int		check_params(char *line, sett_data *settings)
{
	int i;
	int r;

	i = -1;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
		r = set_resolution(line, settings, i);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		r = path_textures(line, settings->north_texture, i);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		r = path_textures(line, settings->south_texture, i);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		r = path_textures(line, settings->east_texture, i);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		r = path_textures(line, settings->west_texture, i);
	else if (line[i] == 'S')
		r = path_textures(line, settings->sprite_texture, i);
	else if (line[i] == 'F')
		r = set_color(line, settings->floor_color, i);
	else if (line[i] == 'C')
		r = set_color(line, settings->ceiling_color, i);
	return (r);
}
