/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:07:07 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/09 16:17:05 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*copy_line(char *line, int mapx)
{
	int		i;
	char	*s;

	i = ft_strlen(line);
	s = (char *)malloc(sizeof(char) * (mapx + 1));
	if (!s)
		return (NULL);
	i = -1;
	while (line[++i])
		s[i] = line[i];
	while (i < mapx)
		s[i++] = ' ';
	s[i] = '\0';
	return (s);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_valid_char(char c)
{
	if (c == '0' || c == '2' || is_player(c))
		return (1);
	return (0);
}
