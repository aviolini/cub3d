/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:38:09 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/15 11:33:27 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parsing_map(char *line, char ***map, int *eof)
{
	if (if_empty_line_and_slide_spaces(line) == -1)
	{
		if (!*map)
			return (1);
		else
		{
				*eof = 1;
				return (1);
		}
	}
	if (*eof || !check_first_number(line))
		return (0);
	if (!(*map = build_map(line,*map)))
		return (0);
	return (1);
}

char	**build_map(char *line, char **map)
{
	int i;
	int y;
	char **m;

	y = ft_matrlen(map);
	if (!(m = (char **)malloc(sizeof(char *) * (y + 2))))
		return (NULL);
	y = 0;
	if (map)
	{
		y = -1;
		while (map[++y])
			if(!(m[y] = copy_and_free_line(map[y])))
				return (NULL);
		//free(map[y]);     /FREE DELL'ULTIMO ELEMENTO CHE e' == NULL?
	}
	i = ft_strlen(line);
	if (!(m[y] = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (line[++i])
		m[y][i] = line[i];
	m[y][i] = '\0';
	m[++y] = NULL;
	return (m);
}

char	*copy_and_free_line(char *line)
{
	int i;
	char *s;

	i = ft_strlen(line);
	if (!(s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (line[++i])
		s[i] = line[i];
	s[i] = '\0';
	free(line);
	return (s);
}

int		check_map(char **map)
{
	//CONTROLLO DEI VALORI DELLA VERA MAPPA 0 e 1
	return (1);
}
