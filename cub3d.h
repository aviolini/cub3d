/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 16:57:26 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/01 10:34:47 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct  b_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			size_pixel;
	int 		xn;
	int 		yn;

}               img_data;

typedef struct	a_data
{
	void		*mlx;
	void		*win;
	img_data	*img_s;
	char		**map;
}				win_data;

typedef struct c_data
{

}				map_data;

#endif
