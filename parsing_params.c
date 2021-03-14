/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:34:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/14 19:11:14 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parsing_params(char *line, sett_data *settings)
{
	int i;
	int r;

	r = 0;
	if((i = if_empty_line_and_slide_spaces(line)) == -1)
		return (1);
	if (line[i] == 'R')
		r = set_resolution(line, settings, i + 1);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		r = path_texture(line, &settings->north_texture, i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		r = path_texture(line, &settings->south_texture, i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		r = path_texture(line, &settings->east_texture, i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		r = path_texture(line, &settings->west_texture, i + 2);
	else if (line[i] == 'S')
		r = path_texture(line, &settings->sprite_texture, i + 1);
	else if (line[i] == 'F')
		r = set_color(line, &settings->floor_color, i + 1);
	else if (line[i] == 'C')
		r = set_color(line, &settings->ceiling_color, i + 1);
	return (r);
}

int		set_resolution(char *line, sett_data *settings, int i)
{
	if (settings->width_win || settings->heigth_win)
		return (0);
	while(!is_digit(line[i]))
		if (line[i++] != ' ' || !line[i])
			return (0);
	while(is_digit(line[i]))
		settings->width_win = settings->width_win * 10 + (line[i++] - 48);
	while(!is_digit(line[i]))
		if (line[i++] != ' ' || !line[i])
			return (0);
	while(is_digit(line[i]))
		settings->heigth_win = settings->heigth_win * 10 + (line[i++] - 48);
	while (line[i])
		if (line[i++] != ' ')
			return (0);
	return (1);
}

int		path_texture(char *line, char **texture, int i)
{
	int z;
	int c;

	z = 0;
	c = 0;
	if (*texture)
		return (0);
	while (line [i] && line[i] == ' ')
		i++;
	z = i;
	while (line[i])
	{
		if (line[i] == ' ' && line[i - 1] != '\\')
			break;
		i++;
	}
	c = i;
	while (line[c])				/* CONTROLLO 'solo spazi'  */
		if (line[c++] != ' ')	/* NEL RESTO DELLA STRINGA */
			return (0);
	c = i - z;
	if (!(*texture = (char *)malloc(sizeof(char) * (c + 1))))
		return (0);
	i = 0;
	while (i < c)
			texture[0][i++] = line[z++];
	texture[0][i] = '\0';
	return (1);
}

int		set_color(char *line, int *color, int i)
{
	int r;
	int g;
	int b;

	if (*color)
		return (0);
	while(!is_digit(line[i]))
		if (line[i++] != ' ' || !line[i])
			return (0);
	r = find_color(line, i);
	if ((i = slide_char(line,i)) == -1)
		return (0);
	g = find_color(line, i);
	if ((i = slide_char(line,i)) == -1)
		return (0);
	b = find_color(line, i);
	while (is_digit(line[i]))
		i++;
	while(line[i])
		if (line[i++] != ' ')
			return (0);
	*color = (r << 16 | g << 8 | b);
	return (1);
}
