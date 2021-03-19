/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:36:22 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/19 10:59:21 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		image(win_data *win)
{
	new_image(win, &win->world);
	new_image(win, &win->view);
	if(!build_world(&win->world, win->settings.map, &win->player))
		return (0);
	return (1);
}

int		build_view(win_data *win)
{
	view_background(&win->view);

	return (1);
}
