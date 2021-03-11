/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:35:54 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/11 19:44:53 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 	is_digit(char c)
{
	if (c >= '0' && c<= '9')
		return (1);
	return (0);
}

int		find_color(char *line, int i)
{
	int color;

	color = 0;
	while (is_digit(line[i]))
		color = color * 10 + line[i++] - 48;
	return (color);
}
