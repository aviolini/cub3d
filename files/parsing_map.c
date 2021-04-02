/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:38:09 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/02 10:22:24 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		parsing_map(char *line, t_settings *settings)
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
	if (!(settings->map = build_map(line, settings->map, &settings->mapW, &settings->mapH)))
		return (0);
	return (1);
}

char	**build_map(char *line, char **map, int *mapx, int *mapy)
{
	int i;
	int y;
	char **m;

	if (!(m = (char **)malloc(sizeof(char *) * (*mapy + 2))))
		return (NULL);
	i = ft_strlen(line);
	if ( i > *mapx)
		*mapx = i;
	y = 0;
	if (map)
		while (map[y])
		{
			if(!(m[y] = copy_line(map[y], *mapx)))
				return (NULL);
			free(map[y++]);
		}
	if(!(m[y] = copy_line(line, *mapx)))
		return (NULL);
	m[++y] = NULL;
	free(map);
	*mapy = y;
	return (m);
}

void print_sprite(t_window *win)
{
	int i;
	i = 0;

	while(i <win->settings.num_of_sprite )
	{
		printf("sprite %d : x:%d , y:%d\n\n", i,win->sprite[i]->sprX,win->sprite[i]->sprY);
		i++;
	}
}

t_sprite **init_sprite(t_window *win,int x, int y)
{
	int i;
	t_sprite **temp;

	if(!(temp = (t_sprite **)malloc(sizeof(t_sprite *) * (win->settings.num_of_sprite))))
		return (0);
		i = 0;
		while(i < win->settings.num_of_sprite)
		{
			if (!(temp[i] = (t_sprite *)malloc(sizeof(t_sprite))))
				return (0);
			if(i < win->settings.num_of_sprite-1)
				temp[i] = win->sprite[i];
			else
			{
				temp[i]->sprX = x;
				temp[i]->sprY = y;
			}
			i++;

			//win->sprite[i++] = NULL;
		}
	return (temp);

}

int		check_map(t_window *win, char **map, int mapy, int mapx)
{
	int y;
	int x;

	y = -1;
	while (++y < mapy && -2 < (x = -1))
		while (++x < mapx)
			if ((map[y][x]) != '1' && map[y][x] != ' ')
			{
				if (!is_valid_char(map[y][x])
				|| (y == 0 || y == mapy - 1)
				|| (x == 0 || x == mapx - 1)
				|| (map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
				|| (map[y][x - 1] == ' ' || map[y][x + 1] == ' '))
					return (0);
				if (is_player(map[y][x]))
				{
					if (win->player.def == 1)
						return (0);
					init_player(&win->player, map[y][x], x, y);
				}
				if (map[y][x] == '2')
				{
					win->settings.num_of_sprite++;
					win->sprite = init_sprite(win,x,y);
				}
			}
//	if (!init_sprite(win))
	//	return (0);
	print_sprite(win);

	return (1);
}


/*
int 	init_sprite(t_window *win)
{
	int			i;

	if(!(win->sprite = (t_sprite **)malloc(sizeof(t_sprite *) * (win->settings.num_of_sprite + 1))))
		return (0);
	i = 0;
	while(i < win->settings.num_of_sprite)
	{
		if (!(win->sprite[i] = (t_sprite *)malloc(sizeof(t_sprite))))
			return (0);
		win->sprite[i]->sprX = 0;
		win->sprite[i]->sprY = 0;
		i++;
		//win->sprite[i++] = NULL;
	}
	win->sprite[i] = NULL;
	return (1);
}
*/
void	init_player(t_player *player, char c,int x, int y)
{
	player->def = 1;
	player->posX = x;// * SCALE;// + SCALE / 2;
	player->posY = y;// * SCALE;// + SCALE / 2;
	if (c == 'N')
		player->angle = M_PI_2;
	else if (c == 'S')
		player->angle = 3*M_PI_2;
	else if (c == 'E')
		player->angle = 0;
	else if (c == 'W')
		player->angle = M_PI;
	player->dirX = cos(player->angle);
	player->dirY = -sin(player->angle);
}
