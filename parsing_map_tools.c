/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:07:07 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/15 01:00:11 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_first_number(char *line)
{
	int i;

	i = 0;
	while(line[i] && line[i] != '1')
		if (line[i++] != ' ')
			return (0);
	return (1);
}

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int		ft_matrlen(char **m)
{
	int i;

	i = 0;
	if (!m)
		return (0);
	while (m[i])
		i++;
	return (i);
}
