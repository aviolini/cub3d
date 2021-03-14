/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:38:09 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/14 23:17:03 by aviolini         ###   ########.fr       */
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
			if(!*eof)
			{
				*eof = 1;
				return (1);
			}
			else
				return (0);
		}
	}
	if (!check_first_number(line))
		return (0);
	if (!build_map(line,map))
		return (0);
	return (1);
}
int		build_map(char *line, char ***map)
{
	if (!(*map = ft_map(line,*map)))
		return (0);
	return (1);
}

char	**ft_map(char *line, char **map)
{
	int i;
	int y;
	char **m;

	y = ft_matrlen(map);
	if (!(m = (char **)malloc(sizeof(char *) * (y + 2))))
		return (NULL);
	y = 0;
	if (map && -2 < (y = -1))
		while (map[++y])
			if(!(m[y] = copy_line(map[y])))
				return (NULL);
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

char	*copy_line(char *line)
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
