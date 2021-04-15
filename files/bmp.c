/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:25:12 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/14 18:28:25 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	bmp_print(t_window *win, int fd)
{
	int	x;
	int	y;
	int	dst;
	int	resx;
	int	resy;

	resx = win->settings.winW;
	resy = win->settings.winH;
	y = resy - 1;
	dst = 0;
	while (y >= 0)
	{
		x = 0;
		while (x < resx)
		{
			dst = (*(int *)(win->view.addr + \
				(y * win->view.line_length + (x * 4))));
			write(fd, &dst, 4);
			x++;
		}
		y--;
	}
}

void	bmp_header_2(t_window *win, int fd)
{
	int	plane;
	int	color;
	int	imgsize;
	int	resx;
	int	resy;

	plane = 1;
	color = 0;
	resx = win->settings.winW;
	resy = win->settings.winH;
	imgsize = resx * (resy - 1) * 4;
	write(fd, &plane, 2);
	write(fd, &win->view.bits_per_pixel, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &imgsize, 4);
	write(fd, &color, 4);
	write(fd, &color, 4);
	write(fd, &color, 4);
	write(fd, &color, 4);
}

void	bmp_header(t_window *win, int fd)
{
	int	filesize;
	int	offset;
	int	infoheader;
	int	resx;
	int	resy;

	offset = 54;
	infoheader = 40;
	resx = win->settings.winW;
	resy = win->settings.winH;
	filesize = resx * resy * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &filesize, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &offset, 4);
	write(fd, &infoheader, 4);
	write(fd, &resx, 4);
	write(fd, &resy, 4);
}

int	ft_bitmap(t_window *win)
{
	int	fd;

	win->settings.minimap_def = 2;
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY, 00755);
	bmp_header(win, fd);
	bmp_header_2(win, fd);
	bmp_print(win, fd);
	close(fd);
	ft_exit(win);
	return (1);
}
