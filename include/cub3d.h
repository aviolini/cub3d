/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:45:51 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/07 15:13:58 by aviolini         ###   ########.fr       */
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
#include <string.h>

#define MLX_SYNC_IMAGE_WRITABLE    1
#define MLX_SYNC_WIN_FLUSH_CMD     2
#define MLX_SYNC_WIN_CMD_COMPLETED 3

#define BUFFER_SIZE 1024
#define SCALE 16
#define SPEED 10
#define FACTOR 0.1
#define H_TEX 64
#define W_TEX 64
#define ROTATION M_PI/84
#define W_IMG 1200
#define H_IMG 600
#define FOV M_PI/3
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define	CYAN 0x0000FFFF
#define PINK 0x00FF00FF
#define YELLOW 0x00FFFF
#define BLACK 0x00000000
#define WHITE 0x00FFFFFF
#define MY_MAX_LIMIT 1000000000

typedef struct s_key
{
	int			e;
	int			w;
	int			a;
	int			s;
	int			d;
	int			l;
	int			r;
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
	int 		visible;
	double 		angle;
	double		distance;
	double 		perpDistance;
	double		spriteWidth;
	double		spriteHeight;
	double		spriteTopY;
	double		spriteBottomY;
	double		spriteAngle;
	double		spriteScreenPosX;
	double		spriteLeftX;
	double		spriteRightX;



	int			i;
	int			is_horiz;

}				t_sprite;

typedef struct	s_image_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct	s_player_data
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	int			def;
	double		angle;
}				t_player;

typedef	struct	s_settings_data
{
	char		**map;
	int			win_def;
	int			winW;
	int			winH;
	char		*north_texture;
	char		*west_texture;
	char		*east_texture;
	char		*south_texture;
	char		*sprite_texture;
	int			floor_color;
	int			ceiling_color;
	int			eof;
	int			winMyW;
	int			winMyH;
	int			mapW;
	int			mapH;
	int			num_of_sprite;
}				t_settings;

typedef struct s_rays_data
{
	double 		angle;
	double		dirX;
	double		dirY;
	double		hitX;
	double		hitY;
	double		*distance;
	int			verticalHit;

	double		indexTex;


	double		value_x;
	double		value_y;
	double		horx;
	double		hory;
	double		verx;
	double		very;
//	double		rayx;
//	double		rayy;
	int			hashity;

}				t_ray;

typedef struct	s_window_data
{
	void		*mlx;
	void		*win;
	t_image		world;
	t_image		view;
	t_player	player;
	t_settings	settings;
	t_ray		ray;
	t_texture	texture[5];
	t_sprite	**sprite;
	t_key		key;
}				t_window;

/*TO_TRASH*/
void	print_tex(t_texture texture);
int 	set_wall_color(int o);
int		build_world(t_image *world, char **map, t_player *player);
void	ray(t_window *win);
void	bundle_ray(t_window *win);
void	print_settings(t_settings settings);
void	print_player(t_player player);
void	print_ray(t_ray ray);
void	miniray(t_window *win);
void	my_mlx_pixel_wall(t_image *img, int x, int y, int color);
void	my_mlx_pixel_grid(t_image *img, int x, int y, int color);
/*CUB3D.C*/
int		main_parsing(char *av, t_window *win);
int		main_window(t_window *win);
void	init_settings(t_settings *settings);

/*SPRITES>c*/

int		visible_sprites(t_window *win, t_sprite *visibleSprites,int *numVisibleSprites);
void 	sort_sprite(t_sprite *visibleSprites,int numVisibleSprites );
void	settings_sprite(t_window *win, t_sprite *visibleSprites, int i);
void	show_sprite(t_window *win,t_sprite *visibleSprites,int i);
int		sprite(t_window *win);

/*KEY*/
int		key(t_window *win);
int		init_key(t_key *key);
int		release_key(int keycode, t_window *win);
int		press_key(int keycode, t_window *win);
int		key_hook(int keycode ,t_window *win);
void	move(char **map, t_player *player, char var);
void	slide(char **map, t_player *player, char var);
void	rotate(t_player *player, char var);
int		ft_exit(t_window *win);
/*IMAGE.C*/
int		sprite(t_window *win);
int		build_view(t_window *win);
int		image(t_window *win);
void	check_hor_intersection(t_window *win, t_settings *settings, t_player player, t_ray *ray);
void	check_ver_intersection(t_window *win, t_settings *settings, t_player player, t_ray *ray);
/*IMAGE_TOOLS*/
int		sprite_intersections(t_window *win, t_sprite **sprite, double x, double y,int i);
void	new_image(t_window *win, t_image *img);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	view_background(t_image *view, t_settings *settings);
void	my_mlx_put_wall(t_window *win, t_image *img, int x, int color);
void	set_right_resolution(t_window *win);
int		init_textures(t_window *win);
void	column(t_window *win, t_image *img,int x,int orientation);
//oid	set_ray(t_player player, t_ray *ray);
int	set_distance_and_wall_orientation(t_player player, t_ray *ray,int i);


/*PARSING MAP */
int		parsing_map(char *line, t_settings *settings);
char	**build_map(char *line, char **map, int *x, int *y);
int		check_map(t_window *win, char **map, int mapy, int mapx);
void	init_player(t_player *player, char c,int x, int y);
/*PARSING MAP_TOOLS*/
int		ft_strlen(char *s);
char	*copy_line(char *line, int mapx);
int		is_player(char c);
int		is_valid_char(char c);
/*PARSING_PARAMS*/
int		parsing_params(char *line, t_settings *settings);
int		set_resolution(char *line, t_settings *settings, int i);
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
int		all_params(t_settings *settings);
/* GNL FUNCTIONS */
int		get_next_line(int fd, char **line);
void	ft_index(char *index, char *ptr, int x);
int		ft_read(int fd, char **line, char *index);
int		ft_strchr(char *str);
char	*ft_newline(char **line, char *ptr, int r);
int		ft_refresh_index(char **line, char *index);
void	ft_clean(char *ptr);

#endif
