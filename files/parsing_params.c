/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:34:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 14:51:47 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parsing_params(char *line, t_settings *settings)
{
	int	i;
	int	r;

	r = 0;
	i = if_empty_line_and_slide_spaces(line);
	if (i == -1)
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

int	set_resolution(char *line, t_settings *settings, int i)
{
	if (settings->winW || settings->winH)
		return (0);
	while (!is_digit(line[i]))
		if (line[i++] != ' ' || !line[i])
			return (0);
	while (is_digit(line[i]))
		settings->winW = settings->winW * 10 + (line[i++] - 48);
	while (!is_digit(line[i]))
		if (line[i++] != ' ' || !line[i])
			return (0);
	while (is_digit(line[i]))
		settings->winH = settings->winH * 10 + (line[i++] - 48);
	while (line[i])
		if (line[i++] != ' ')
			return (0);
	return (1);
}

int	path_texture(char *line, char **texture, int i)
{
	int	z;
	int	c;

	if (*texture)
		return (0);
	while (line [i] && line[i] == ' ')
		i++;
	z = i;
	while (line[i])
		i++;
	c = i;
	while (line[c])
		if (line[c++] != ' ')
			return (0);
	c = i - z;
	*texture = (char *)malloc(sizeof(char) * (c + 1));
	if (!*texture)
		return (0);
	i = 0;
	while (i < c)
		texture[0][i++] = line[z++];
	texture[0][i] = '\0';
	if (!control_path(texture[0]))
		return (0);
	return (1);
}

int	set_color(char *line, unsigned int *color, int i)
{
	int	rgb[3];
	int	x;

	if (*color != INIT_COLOR)
		return (0);
	x = 0;
	i = find_color(&rgb[0], line, i);
	if (i == -1)
		return (0);
	while (++x <= 2)
	{
		i = slide_char(line, i);
		if (i == -1)
			return (0);
		i = find_color(&rgb[x], line, i);
		if (i == -1)
			return (0);
	}
	while (line[i])
		if (line[i++] != ' ')
			return (0);
	*color = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	return (1);
}

int	control_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	close(fd);
	if (fd < 0)
		return (0);
	return (1);
}
