/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:45:51 by aviolini          #+#    #+#             */
/*   Updated: 2021/03/21 16:13:14 by aviolini         ###   ########.fr       */
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
#define SCALE 16
#define SPEED 5
#define ROTATION M_PI/12
#define W_IMG 600
#define H_IMG 480
#define FOV M_PI/3
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF
#define BLACK 0x00000000
#define WHITE 0x00FFFFFF

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
	int			speed;
	int			def;
	double		angle;
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
	int			mapx;
	int			mapy;
}				sett_data;

typedef struct rays_data
{
	double		horx;
	double		hory;
	double		verx;
	double		very;
	double		rayx;
	double		rayy;
	double		distance;

}				ray_data;

typedef struct	window_data
{
	void		*mlx;
	void		*win;
	img_data	world;
	img_data	view;
	pl_data		player;
	sett_data	settings;
	ray_data	ray;
}				win_data;

/*TO_TRASH*/
int		build_world(img_data *world, char **map, pl_data *player);
void	ray(win_data *win);
void	bundle_ray(win_data *win);
void	print_settings(sett_data settings);
void	print_player(pl_data player);
void	print_ray(ray_data ray);
void	miniray(win_data *win);
void	my_mlx_pixel_wall(img_data *img, int x, int y, int color);
void	my_mlx_pixel_grid(img_data *img, int x, int y, int color);
/*CUB3D.C*/
int		main_parsing(char *av, sett_data *settings, pl_data *player);
int		main_window(win_data *win);
void	init_settings(sett_data *settings);
/*KEY*/
int		key_hook(int keycode, win_data *win);
void	move(char **map, pl_data *player, char var);
void	slide(char **map, pl_data *player, char var);
void	rotate(pl_data *player, char var);
int		ft_exit(win_data *win);
/*IMAGE.C*/
int		build_view(win_data *win);
int		image(win_data *win);
void	check_hor_intersection(win_data *win, sett_data *settings, pl_data player, ray_data *ray);
void	check_ver_intersection(win_data *win, sett_data *settings, pl_data player, ray_data *ray);
/*IMAGE_TOOLS*/
void	new_image(win_data *win, img_data *img);
void	my_mlx_pixel_put(img_data *img, int x, int y, int color);
void	view_background(img_data *view);
void	my_mlx_pixel_put3(img_data *img, double x, double y,double h, int color);
void	set_right_resolution(win_data *win);
void	set_ray(pl_data player, ray_data *ray);



/*PARSING MAP */
int		parsing_map(char *line, sett_data *settings);
char	**build_map(char *line, char **map, int *x, int *y);
int		check_map(char **map, int mapy, int mapx, pl_data *player);
void	init_player(char c,int x, int y, pl_data *player);
/*PARSING MAP_TOOLS*/
int		ft_strlen(char *s);
char	*copy_line(char *line, int mapx);
int		is_player(char c);
int		is_valid_char(char c);
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
int		slide_char(char *line, int i);
int		find_color(char *line, int i);
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
