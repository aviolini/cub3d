/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:38:09 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 11:36:41 by aviolini         ###   ########.fr       */
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
	i = ft_strlen(line);
	if (i > *mapx)
		*mapx = i;
	y = 0;
	if (map)
	{
		while (map[y])
		{
			m[y] = copy_line(map[y], *mapx);
			free(map[y++]);
		}
	}
	m[y] = copy_line(line, *mapx);
	m[++y] = NULL;
	free(map);
	*mapy = y;
	return (m);
}

int	check_map(t_window *win, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < win->settings.mapH)
	{
		x = -1;
		while (++x < win->settings.mapW)
		{
			if ((map[y][x]) != '1' && map[y][x] != ' ')
			{
				if (!is_a_valid_char(map[y][x]) || \
					(!is_a_protected_zero(win, map, x, y)))
					return (0);
				if (is_player(map[y][x]))
					if (!init_player(win, map[y][x], x, y))
						return (0);
				if (map[y][x] == '2')
					init_sprite(win, x, y);
			}
		}
	}
	if (win->settings.player_def == 0)
		return (0);
	return (1);
}

int	init_player(t_window *win, char c, int x, int y)
{
	if (win->settings.player_def == 0)
		win->settings.player_def = 1;
	else
		return (0);
	win->player.posX = x;
	win->player.posY = y;
	if (c == 'N')
		win->player.angle = M_PI_2;
	else if (c == 'S')
		win->player.angle = 3 * M_PI_2;
	else if (c == 'E')
		win->player.angle = 0;
	else if (c == 'W')
		win->player.angle = M_PI;
	win->player.dirX = cos(win->player.angle);
	win->player.dirY = -sin(win->player.angle);
	return (1);
}

int	init_sprite(t_window *win, int x, int y)
{
	int			i;
	t_sprite	**temp;

	win->settings.num_sprites++;
	temp = (t_sprite **)malloc(sizeof(t_sprite *) * \
			(win->settings.num_sprites));
	i = 0;
	while (i < win->settings.num_sprites - 1)
	{
		temp[i] = (t_sprite *)malloc(sizeof(t_sprite));
		*temp[i] = *win->sprites[i];
		free(win->sprites[i]);
		i++;
	}
	temp[i] = (t_sprite *)malloc(sizeof(t_sprite));
	temp[i]->sprX = x + 0.5;
	temp[i]->sprY = y + 0.5;
	if (win->sprites)
		free(win->sprites);
	win->sprites = temp;
	return (1);
}
