/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:38:09 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/18 12:58:38 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parsing_map(char *line, sett_data *settings)
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
	if (settings->eof || !check_first_number(line))
		return (0);
	if (!(settings->map = build_map(line,settings->map,&settings->mapx, &settings->mapy)))
		return (0);
	return (1);
}

char	**build_map(char *line, char **map, int *mapx, int *mapy)
{
	int i;
	int y;
	char **m;

	y = ft_matrlen(map);
	if (!(m = (char **)malloc(sizeof(char *) * (y + 2))))
		return (NULL);
	y = 0;
	i = ft_strlen(line);
	if ( i > *mapx)
		*mapx = i;
	if (map)
	{
		y = -1;
		while (map[++y])
			if(!(m[y] = copy_and_free_line(map[y], *mapx)))
				return (NULL);
		//free(map[y]);     /FREE DELL'ULTIMO ELEMENTO CHE e' == NULL?
	}
	i = ft_strlen(line);
	if (!(m[y] = (char *)malloc(sizeof(char) * (*mapx + 1))))
		return (NULL);
	i = -1;
	while (line[++i])
		m[y][i] = line[i];
	while (i < *mapx)
		m[y][i++] = ' ';
	m[y][i] = '\0';
	m[++y] = NULL;
	*mapy = y;
	return (m);
}

char	*copy_and_free_line(char *line, int mapx)
{
	int i;
	char *s;

	i = ft_strlen(line);
	if (!(s = (char *)malloc(sizeof(char) * (mapx + 1))))
		return (NULL);
	i = -1;
	while (line[++i])
		s[i] = line[i];
	while (i < mapx)
		s[i++] = ' ';
	s[i] = '\0';
	free(line);
	return (s);
}

int		check_map(char **map)
{
	(void)map;
	//CONTROLLO DEI VALORI DELLA VERA MAPPA 0 e 1
	return (1);
}
