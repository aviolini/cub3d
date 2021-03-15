/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:45:51 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/15 10:24:58 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

#define BUFFER_SIZE 1024
#define W_IMG 600
#define H_IMG 480
#define	FOV_ANGLE M_PI/3

typedef struct	image_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			size_pixel;
}				img_data;

typedef struct	player_data
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		angle;
	int			speed;
}				pl_data;

typedef	struct	settings_data
{
	char		**map;
	int			win_resx;
	int			win_resy;
	char		*north_texture;
	char		*west_texture;
	char		*east_texture;
	char		*south_texture;
	char		*sprite_texture;
	int			floor_color;
	int			ceiling_color;
	int			eof;
	int			win_my_resx;
	int			win_my_resy;
}				sett_data;

typedef struct	window_data
{
	void		*mlx;
	void		*win;
	img_data	world;
	img_data	img;
	pl_data		player;
	sett_data	settings;
}				win_data;

/*CUB3D.C*/
int		parsing_file(char *av, sett_data *settings);
void	init_settings(sett_data *settings);
void	print_settings(sett_data *settings);
/*MANAGE WINDOW*/
int		main_window(win_data *win);
void	init_player(pl_data *player);
void	print_player(pl_data *player);
/*MANAGE WINDOW TOOLS*/
void		set_right_resolution(win_data *win);

/*PARSING MAP */
int		parsing_map(char *line, char ***map, int *eof);
char	**build_map(char *line, char **map);
char	*copy_and_free_line(char *line);
int		check_map(char **map);
/*PARSING MAP_TOOLS*/
int		check_first_number(char *line);
int		ft_strlen(char *s);
int		ft_matrlen(char **m);
/*PARSING_PARAMS*/
int		parsing_params(char *line, sett_data *settings);
int		set_resolution(char *line, sett_data *settings, int i);
int		path_texture(char *line, char **texture, int i);
int		set_color(char *line, int *color, int i);
/*CHECK MAIN ARGS TOOLS*/
int		check_argv2(char *av);
int		check_argv1(char *av);
int		check_args(int ac, char **av);
/*PARSING PARAMS TOOLS*/
int 	is_digit(char c);
int		if_empty_line_and_slide_spaces(char *line);
int		find_color(char *line, int i);
int		slide_char(char *line, int i);
int		all_params(sett_data *settings);
/* GNL FUNCTIONS */
int		get_next_line(int fd, char **line);
void	ft_index(char *index, char *ptr, int x);
int		ft_read(int fd, char **line, char *index);
int		ft_strchr(char *str);
char	*ft_newline(char **line, char *ptr, int r);
int		ft_refresh_index(char **line, char *index);
void	ft_clean(char *ptr);

#endif
