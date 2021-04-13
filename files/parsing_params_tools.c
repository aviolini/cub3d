/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_params_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:35:54 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 14:52:23 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int 	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	if_empty_line_and_slide_spaces(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\0')
		return (-1);
	while (line[i] == ' ')
		if (line[++i] == '\0')
			return (-1);
	return (i);
}

int	slide_char(char *line, int i)
{
	while (line[i] != ',')
	{
		if (line[i] != ' ' || !line[i + 1])
			return (-1);
		i++;
	}
	i++;
	return (i);
}

int	find_color(int *rgb, char *line, int i)
{
	int	color;

	color = 0;
	while (!is_digit(line[i]))
		if (line[i++] != ' ' || !line[i])
			return (-1);
	while (is_digit(line[i]))
		color = color * 10 + line[i++] - 48;
	if (color > 255 || color < 0)
		return (-1);
	*rgb = color;
	return (i);
}

int	all_params(t_settings *settings)
{
	if (!settings->winW)
		return (0);
	if (!settings->winH)
		return (0);
	if (!settings->north_texture)
		return (0);
	if (!settings->west_texture)
		return (0);
	if (!settings->east_texture)
		return (0);
	if (!settings->south_texture)
		return (0);
	if (!settings->sprite_texture)
		return (0);
	if (settings->floor_color == INIT_COLOR)
		return (0);
	if (settings->ceiling_color == INIT_COLOR)
		return (0);
	return (1);
}
