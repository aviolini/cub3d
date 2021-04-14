/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:45:51 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/14 12:31:05 by aviolini         ###   ########.fr       */
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
# include <errno.h>
# include <string.h>

# define BUFFER_SIZE 1024
# define SCALE 10
# define FACTOR 0.35
# define ROTATION 0.06545
# define MIN_RES_W 854
# define MIN_RES_H 480
# define FOV 1.0472
# define INIT_COLOR 0xFFFFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define CYAN 0x0000FFFF
# define PINK 0x00FF00FF
# define YELLOW 0xFFFF00
# define BLACK 0x00000000
# define GRAY 0x888888
# define WHITE 0x00FFFFFF
# define TRANSP 0xFFFFFFFF
# define MY_MAX_LIMIT 1000000000

typedef struct s_draw_utils
{
	double		dist_proj_plane;
	double		start_topY;
	double		end_bottomY;
	double		perp_distance;
	double		h_object;
	double		distance_from_top;
	int			offsetX;
	int			offsetY;
	double		texel_width;
}				t_draw_utils;

typedef struct s_key
{
	int			e;
	int			w;
	int			a;
	int			s;
	int			d;
	int			l;
	int			r;
	int			m;
}				t_key;

typedef struct s_texture_data
{
	void		*tex;
	int			texW;
	int			texH;
	int			*addr;
}				t_texture;

typedef struct s_sprite_data
{
	double		sprX;
	double		sprY;
	double		angle;
	double		distance;
	double		perp_distance;
	double		sprite_width;
	double		sprite_height;
	double		sprite_topY;
	double		sprite_bottomY;
	double		sprite_screen_posX;
	double		sprite_leftX;
	double		sprite_rightX;
}				t_sprite;

typedef struct s_image_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_player_data
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	int			def;
	double		angle;
}				t_player;

typedef struct s_settings_data
{
	char			**map;
	int				win_def;
	int				img_def;
	int				player_def;
	int				minimap_def;
	unsigned int	winW;
	unsigned int	winH;
	int				dist_proj_plane;
	char			*north_texture;
	char			*west_texture;
	char			*east_texture;
	char			*south_texture;
	char			*sprite_texture;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				eof;
	int				winMyW;
	int				winMyH;
	int				mapW;
	int				mapH;
	int				num_sprites;
	int				save;
}					t_settings;

typedef struct s_rays_data
{
	double		angle;
	double		dirX;
	double		dirY;
	double		*distance;
	double		indexTex;
	double		value;
	int			round;
	double		horX;
	double		horY;
	double		verX;
	double		verY;
}				t_ray;

typedef struct s_window_data
{
	void			*mlx;
	void			*win;
	t_image			world;
	t_image			view;
	t_player		player;
	t_settings		settings;
	t_ray			ray;
	t_texture		textures[5];
	t_sprite		**sprites;
	t_key			key;
	t_draw_utils	draw;
}					t_window;

/*MAIN*/
int		main_parsing(char *av, t_window *win);
int		main_window(t_window *win);
void	init_env(t_window *win);
/*CHECK MAIN ARGS TOOLS*/
int		check_argv2(char *av);
int		check_argv1(char *av);
int		check_args(int ac, char **av);
/*PARSING MAP */
int		parsing_map(char *line, t_settings *settings);
char	**build_map(char *line, char **map, int *x, int *y);
int		check_map(t_window *win, char **map);
int		init_player(t_window *win, char c, int x, int y);
int		init_sprite(t_window *win, int x, int y);
/*PARSING MAP TOOLS*/
int		ft_strlen(char *s);
char	*copy_line(char *line, int mapx);
int		is_player(char c);
int		is_a_valid_char(char c);
int		is_a_protected_zero(t_window *win, char **map, int x, int y);
/*PARSING PARAMS*/
int		parsing_params(char *line, t_settings *settings);
int		set_resolution(char *line, t_settings *settings, int i);
int		path_texture(char *line, char **texture, int i);
int		set_color(char *line, unsigned int *color, int i);
int		control_path(char *path);
/*PARSING PARAMS TOOLS*/
int		is_digit(char c);
int		if_empty_line_and_slide_spaces(char *line);
int		slide_char(char *line, int i);
int		find_color(int *rgb, char *line, int i);
int		all_params(t_settings *settings);
/* GNL FUNCTIONS */
int		get_next_line(int fd, char **line);
void	ft_index(char *index, char *ptr, int x);
int		ft_read(int fd, char **line, char *index);
int		ft_strchr(char *str);
char	*ft_newline(char **line, char *ptr, int r);
int		ft_refresh_index(char **line, char *index);
void	ft_clean(char *ptr);
/*IMAGE*/
int		build_view(t_window *win);
int		image(t_window *win);
void	column(t_window *win, t_image *img, int x, int orientation);
int		sprite(t_window *win);
/*IMAGE TOOLS*/
void	new_image(t_window *win, t_image *img);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int		open_texture(t_window *win, int i, char *path);
int		init_textures(t_window *win);
/*IMAGE TOOLS 2*/
double	draw_protect_max(double *value, unsigned int *max);
double	draw_protect_min(double *value);
void	set_right_resolution(t_window *win);
void	view_background(t_image *view, t_settings *settings);
/*INTERSECTIONS*/
void	check_hor_inters(t_settings *settings, t_player player, t_ray *ray);
void	check_ver_inters(t_settings *settings, t_player player, t_ray *ray);
void	set_ray_round_and_ray_value(double dirXorY, t_ray *ray);
int		set_dist_and_wall_orient(t_window *win, \
										t_player player, t_ray *ray, int i);
/*PlAYER*/
void	move(char **map, t_player *player, char var);
void	slide(char **map, t_player *player, char var);
void	rotate(t_player *player, char var);
/*KEY*/
int		init_key(t_key *key);
int		release_key(int keycode, t_window *win);
int		press_key(int keycode, t_window *win);
int		key(t_window *win);
int		ft_exit(t_window *win);
/*SPRITES>c*/
int		visible_sprites(t_window *win, t_sprite *visibleSprites, \
													int *numVisibleSprites);
void	sort_sprites(t_sprite *visibleSprites, int numVisibleSprites);
void	settings_sprite(t_window *win, t_sprite *visibleSprites, int i);
void	draw_sprite_pixel(t_window *win, int x, int y);
void	show_sprites(t_window *win, t_sprite *visibleSprites, int i);
/*MINIMAP*/
void	new_minimap_image(t_window *win, t_image *image);
int		build_world(t_image *world, char **map);
void	my_mlx_pixel_grid(t_image *img, int x, int y);
/*MINIMAP TOOLS*/
void	print_intersection(t_window *win, double intersX, double intersY);
void	miniray(t_window *win);
void	my_mlx_pixel_wall(t_image *img, int x, int y, int color);
void	draw_grid_pixel(t_image *img, int x, int y, int color);
/*BITMAP.C*/
void	bmp_print(t_window *win, int fd);
void	bmp_header_2(t_window *win, int fd);
void	bmp_header(t_window *win, int fd);
int		ft_bitmap(t_window *win);

#endif
