/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:04:00 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/01 19:57:40 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_keycode_left(win_data *win)
{
	int z = 0, j = 0;
		while (j < 14)
			{
				while(win->map_s->map[j][z])
				{
					 if (win->map_s->map[j][z] == 'N' && win->map_s->map[j][z -1] == '0')
					 	{
							win->map_s->map[j][z - 1] = 'N';
							win->map_s->map[j][z] = '0';
						}
					z++;
				}
				z = 0;
				j++;
			}
			j = 0;


			//while ( j < 14)
			//	printf("newmap%s\n",win->map[j++]);
}

void	ft_keycode_up(win_data *win)
{
	int z = 0, j = 0;
		while (j < 14)
			{
				while(win->map_s->map[j][z])
				{
					 if (win->map_s->map[j][z] == 'N' && win->map_s->map[j - 1][z] == '0')
					 	{
							win->map_s->map[j - 1][z] = 'N';
							win->map_s->map[j][z] = '0';
						}
					z++;
				}
				z = 0;
				j++;
			}
			j = 0;


			//while ( j < 14)
			//	printf("newmap%s\n",win->map[j++]);
}

void	ft_keycode_right(win_data *win)
{
	int z = 0, j = 0;
		while (j < 14)
			{
				while(win->map_s->map[j][z])
				{
					 if (win->map_s->map[j][z] == 'N' && win->map_s->map[j][z + 1] == '0')
					 	{
							win->map_s->map[j][z + 1] = 'N';
							win->map_s->map[j][z] = '0';
							return;
						}
					z++;
				}
				z = 0;
				j++;
			}
			j = 0;


			//while ( j < 14)
			//	printf("newmap%s\n",win->map[j++]);
}

void	ft_keycode_down(win_data *win)
{
	int z = 0, j = 0;
		while (j < 14)
			{
				while(win->map_s->map[j][z])
				{
					 if (win->map_s->map[j][z] == 'N' && win->map_s->map[j + 1][z] == '0')
					 	{
							win->map_s->map[j + 1][z] = 'N';
							win->map_s->map[j][z] = '0';
							return;
						}
					z++;
				}
				z = 0;
				j++;
			}
			j = 0;


			//while ( j < 14)
			//	printf("newmap%s\n",win->map[j++]);
}
