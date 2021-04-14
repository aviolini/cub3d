/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 08:53:50 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/14 12:35:06 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_key(t_key *key)
{
	key->e = 0;
	key->w = 0;
	key->a = 0;
	key->s = 0;
	key->d = 0;
	key->l = 0;
	key->r = 0;
	key->m = 0;
	return (1);
}

int	release_key(int keycode, t_window *win)
{
	if (keycode == 53)
		win->key.e = 0;
	if (keycode == 13)
		win->key.w = 0;
	if (keycode == 1)
		win->key.s = 0;
	if (keycode == 2)
		win->key.d = 0;
	if (keycode == 0)
		win->key.a = 0;
	if (keycode == 124)
		win->key.r = 0;
	if (keycode == 123)
		win->key.l = 0;
	return (1);
}

int	press_key(int keycode, t_window *win)
{
	if (keycode == 53)
		win->key.e = 1;
	if (keycode == 13)
		win->key.w = 1;
	if (keycode == 1)
		win->key.s = 1;
	if (keycode == 2)
		win->key.d = 1;
	if (keycode == 0)
		win->key.a = 1;
	if (keycode == 124)
		win->key.r = 1;
	if (keycode == 123)
		win->key.l = 1;
	if (keycode == 46 && win->key.m == 0)
		win->key.m = 1;
	else if (keycode == 46 && win->key.m == 1)
		win->key.m = 0;
	return (1);
}

int	key(t_window *win)
{
	mlx_clear_window(win->mlx, win->win);
	if (win->key.e)
		ft_exit(win);
	if (win->key.w)
		move(win->settings.map, &win->player, 'w');
	if (win->key.s)
		move(win->settings.map, &win->player, 's');
	if (win->key.d)
		slide(win->settings.map, &win->player, 'd');
	if (win->key.a)
		slide(win->settings.map, &win->player, 'a');
	if (win->key.r)
		rotate(&win->player, 'r');
	if (win->key.l)
		rotate(&win->player, 'l');
	if (win->key.m)
		win->settings.minimap_def = 1;
	if (!win->key.m)
		win->settings.minimap_def = 0;
	build_view(win);
	return (0);
}

int	ft_exit(t_window *win)
{
	int	y;

	y = 0;
	while (y < win->settings.mapH)
		free(win->settings.map[y++]);
	free(win->settings.map);
	free(win->settings.north_texture);
	free(win->settings.west_texture);
	free(win->settings.east_texture);
	free(win->settings.south_texture);
	free(win->settings.sprite_texture);
	y = 0;
	while (y < win->settings.num_sprites)
		free(win->sprites[y++]);
	free(win->sprites);
	if (win->settings.minimap_def == 2)
		mlx_destroy_image(win->mlx, win->world.img);
	if (win->settings.img_def == 1)
		mlx_destroy_image(win->mlx, win->view.img);
	if (win->settings.win_def == 1)
		mlx_destroy_window(win->mlx, win->win);
	exit(0);
}
