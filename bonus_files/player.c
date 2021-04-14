/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:03:02 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/13 12:03:46 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move(char **map, t_player *player, char var)
{
	int	value;

	if (var == 'w')
		value = 1;
	if (var == 's')
		value = -1;
	player->posY += (value) * player->dirY * FACTOR;
	player->posX += (value) * player->dirX * FACTOR;
	while ((map[(int)floor(player->posY)][(int)floor(player->posX)] == '1') || \
		(map[(int)floor(player->posY)][(int)floor(player->posX)] == '2') || \
		(map[(int)floor(player->posY)][(int)floor(player->posX)] == ' '))
	{
		player->posY -= (value) * player->dirY * FACTOR;
		player->posX -= (value) * player->dirX * FACTOR;
	}
}

void	slide(char **map, t_player *player, char var)
{
	int	value;

	if (var == 'a')
		value = -1;
	if (var == 'd')
		value = 1;
	player->posY += (value) * player->dirX * FACTOR;
	player->posX -= (value) * player->dirY * FACTOR;
	while ((map[(int)floor(player->posY)][(int)floor(player->posX)] == '1') || \
		(map[(int)floor(player->posY)][(int)floor(player->posX)] == '2') || \
		(map[(int)floor(player->posY)][(int)floor(player->posX)] == ' '))
	{
		player->posY -= (value) * player->dirX * FACTOR;
		player->posX += (value) * player->dirY * FACTOR;
	}
}

void	rotate(t_player *player, char var)
{
	int	value;

	if (var == 'r')
		value = -1;
	if (var == 'l')
		value = 1;
	if (player->angle + (value) * ROTATION > 2 * M_PI)
		player->angle = (value) * ROTATION;
	else if (player->angle + (value) * ROTATION < 0)
		player->angle = 2 * M_PI + (value) * ROTATION;
	else
		player->angle += (value) * ROTATION;
	player->dirX = cos(player->angle);
	player->dirY = -sin(player->angle);
}
