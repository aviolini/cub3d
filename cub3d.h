/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 16:57:26 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/03 14:39:02 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef struct  b_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			size_pixel;
}               img_data;

typedef struct c_data
{
	char		**map;
	int		posx;
	int		posy;
}				map_data;

typedef struct	a_data
{
	void		*mlx;
	void		*win;
	map_data	*map_s;
	img_data	*img_s;
}				win_data;

void	ft_destroy_img(win_data *win);
void	my_mlx_pixel_put(img_data *img, int x, int y, int color);
void	my_mlx_pixel_put2(img_data *img, int x, int y, int color);

char	**ft_build_map (char *buff, int x, int y);
void	ft_build_image(win_data *win, int a);
int		key_hook(int keycode, win_data *win);

void	ft_keycode_left(win_data *win);
void	ft_keycode_right(win_data *win);
void	ft_keycode_up(win_data *win);
void	ft_keycode_down(win_data *win);
void	ft_ray0(win_data *win);
#endif
