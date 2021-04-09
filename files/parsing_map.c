/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:38:09 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/09 13:16:19 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parsing_map(char *line, t_settings *settings)
{
	if (if_empty_line_and_slide_spaces(line) == -1)
	{
		if (!settings->map)
			return (1);
		else
		{
			settings->eof = 1;
			return (1);
		}
	}
	if (settings->eof)
		return (0);
	settings->map = build_map(line, settings->map, &settings->mapW, \
		&settings->mapH);
	if (!settings->map)
		return (0);
	return (1);
}

char	**build_map(char *line, char **map, int *mapx, int *mapy)
{
	int		i;
	int		y;
	char	**m;

	m = (char **)malloc(sizeof(char *) * (*mapy + 2));
	if (!m)
		return (NULL);
	i = ft_strlen(line);
	if (i > *mapx)
		*mapx = i;
	y = 0;
	if (map)
	{
		while (map[y])
		{
			m[y] = copy_line(map[y], *mapx);
			if (!m[y])
				return (NULL);
			free(map[y++]);
		}
	}
	m[y] = copy_line(line, *mapx);
	if (!m[y])
		return (NULL);
	m[++y] = NULL;
	free(map);
	*mapy = y;
	return (m);
}

int	init_sprite(t_window *win, int x, int y)
{
	int			i;
	t_sprite	**temp;

	i = 0;
	win->settings.num_of_sprite++;
	temp = (t_sprite **)malloc(sizeof(t_sprite *) * \
	(win->settings.num_of_sprite));
	if (!temp)
		return (0);
	while (i < win->settings.num_of_sprite - 1)
	{
		temp[i] = (t_sprite *)malloc(sizeof(t_sprite));
		if (!temp[i])
			return (0);
		*temp[i] = *win->sprite[i];
		free(win->sprite[i]);
		i++;
	}
	temp[i] = (t_sprite *)malloc(sizeof(t_sprite));
	if (!temp[i])
		return (0);
	temp[i]->sprX = x + 0.5;
	temp[i]->sprY = y + 0.5;
	if (win->sprite)
		free(win->sprite);
	win->sprite = temp;
	return (1);
}

int	check_map(t_window *win, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < win->settings.mapH)
	{
		while (++x < win->settings.mapW)
		{
			if ((map[y][x]) != '1' && map[y][x] != ' ')
			{
				if (!is_valid_char(map[y][x]) || \
				(y == 0 || y == win->settings.mapH - 1) || \
				(x == 0 || x == win->settings.mapW - 1) || \
				(map[y - 1][x] == ' ' || map[y + 1][x] == ' ') || \
				(map[y][x - 1] == ' ' || map[y][x + 1] == ' ') || \
				(map[y - 1][x - 1] == ' ' || map[y + 1][x + 1] == ' ') || \
				(map[y - 1][x + 1] == ' ' || map[y - 1][x + 1] == ' '))
					return (0);
				if (is_player(map[y][x]))
				{
					if (win->player.def == 1)
						return (0);
					init_player(&win->player, map[y][x], x, y);
				}
				if (map[y][x] == '2')
					init_sprite(win, x, y);
			}
		}
		x = -1;
	}
	return (1);
}

void	init_player(t_player *player, char c, int x, int y)
{
	player->def = 1;
	player->posX = x;
	player->posY = y;
	if (c == 'N')
		player->angle = M_PI_2;
	else if (c == 'S')
		player->angle = 3 * M_PI_2;
	else if (c == 'E')
		player->angle = 0;
	else if (c == 'W')
		player->angle = M_PI;
	player->dirX = cos(player->angle);
	player->dirY = -sin(player->angle);
}
