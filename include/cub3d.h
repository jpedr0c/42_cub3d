/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:32:49 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 10:22:30 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/libft/include/ft_printf.h"
# include "../libraries/libft/include/get_next_line.h"
# include "../libraries/libft/include/libft.h"
# include "../libraries/minilibx_linux/mlx.h"
# include "colors.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define NAME "cub3D"
# define WIDTH 1280
# define HEIGHT 720
# define FLOOR '0'
# define WALL '1'
# if !defined TEX_W || !defined TEX_H
#  define TEX_W 64
#  define TEX_H 64
# endif
# if !defined NO || !defined SO || !defined WE || !defined EA
#  define TEX_NO 0
#  define TEX_SO 1
#  define TEX_WE 2
#  define TEX_EA 3
# endif

# ifdef __linux__

enum			e_keycode
{
	KEY_ESC = 65307,
	KEY_MINUS = 45,
	KEY_PLUS = 61,
	ARROW_LEFT = 65361,
	ARROW_RIGHT = 65363,
	KEY_W = 119,
	KEY_S = 115,
	KEY_A = 97,
	KEY_D = 100,
	KEY_SHIFT = 65505
};
# else

enum			e_keycode
{
	KEY_ESC = 53,
	KEY_MINUS = 27,
	KEY_PLUS = 24,
	ARROW_LEFT = 123,
	ARROW_RIGHT = 124,
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_D = 2,
	KEY_SHIFT = 257
};
# endif

typedef struct s_map
{
	char		start_orientation;
	char		**map;
	char		**buffer;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			width;
	int			height;
	int			frgb;
	int			crgb;
	int			aux;
	int			lines;
	int			index;
	int			count;
	float		p_pos[2];
}				t_map;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_tex
{
	t_img		img;
	int			h;
	int			w;
}				t_tex;

typedef struct s_player
{
	float		pos_x;
	float		pos_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
}				t_player;

typedef struct s_ray
{
	int			map_x;
	int			map_y;
	float		cam_x;
	float		cam_y;
	float		dir_x;
	float		dir_y;
	float		side_dist_x;
	float		side_dist_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			texture_id;
	int			tex_x;
	int			tex_y;
	float		wall_x;
	float		step;
	float		tex_pos;
	float		z_buffer[WIDTH];
}				t_ray;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			right_arrow;
	int			left_arrow;
	int			shift;
}				t_keys;

typedef struct s_game
{
	int			frame;
	t_map		*map;
	t_player	p;
	t_img		img;
	t_tex		tex[5];
	void		*win;
	void		*mlx;
	t_ray		*ray;
	t_keys		keys;
}				t_game;

// CUB3D
int				main(int argc, char **argv);

// CALC_TEXTURE
void			calculate_screen_line(t_ray *ray);
void			calculate_texture_id(t_ray *ray);
void			calculate_wall_coordinate(t_game *game, t_ray *ray);
void			calculate_texture_coordinate(t_game *game, t_ray *ray);
void			calculate_texture_data(t_game *game, t_ray *ray);

// COLORS
int				get_pixel_color(t_img *img, int x, int y);
int				create_rgba(int r, int g, int b, int a);
int				read_colors(t_map **map, int i);
int				process_colors(t_map **map, int i, char **ptr);

// CONFIG
int				initialize_game(t_game *var);
void			init_map(t_map *map);
int				initialize_mlx(t_game *game);
int				fill_buffer(char *file, int lines, t_map *map);

// CONTROLS
void			vertical_player_move(int keycode, t_game *var, float speed);
void			horizontal_player_move(int keycode, t_game *var, float speed);
void			change_vision_player(int keycode, t_game *var, float speed);
void			handle_keypress(t_game *var);

// DDA
void			calculate_step_and_side(t_game *var, t_ray *ray);
void			calculate_delta_distances(t_ray *ray);
void			detect_next_collision(t_ray *ray);
int				check_collision_wall(t_game *var, t_ray *ray);
void			dda(t_game *var, t_ray *ray);

// DRAW
void			img_pixel_put(t_img *img, int x, int y, int color);
void			img_paste_pixel(t_img *img, int x, int y, int pixel);
void			draw_square(t_game *var);
void			draw(t_game *var);
void			draw_vertical_line(t_game *var, t_ray *ray, int x);
void			raycast_wall(t_game *var);

// FREEDOM_SINGS
void			free_split(char **splited);
void			free_map(t_map *map);
void			free_all(t_game *var);
int				free_map_exit(t_map *map, int back);

// GENERATE_MAP
int				read_map(t_map *map, char *str);
void			fill_map(t_map **map);
void			check_width(t_map **map);
int				parse_map(t_map **map);
int				init_parser(t_map *map, char *str);

// INIT_RAYCASTING
void			set_cam_x(t_ray *ray, int x, int win_w);
void			set_ray_directions(t_game *game, t_ray *ray);
void			set_ray_map_pos(t_game *game, t_ray *ray);
void			calculate_delta_distances(t_ray *ray);
void			init_ray(t_game *var, t_ray *ray, int x);

// GAME
int				key_press_hook(int keycode, t_game *game);
int				key_release_hook(int keycode, t_game *game);
int				close_window(t_game *var);
int				game_loop(t_game *var);
int				init_game(t_game *var);

// MAP_UTILS
int				is_existing_texture(char *direction);
void			count_lines(t_map **map, int i);
void			ignore_empty_lines(t_map **map);
int				ignore_spaces(char *line, int i);
int				counter(char c, t_map **map);

// MAP_VALIDATIONS
int				is_array_digit(char **s);
int				is_filled_map(const t_map *map);
int				verify_border(const char *line);
int				line_handler(char *line, int index, t_map **map);
int				last_map_check(t_map **map);

// PLAYER
void			set_dir(t_player *g, int dir_x, int dir_y);
void			set_plane(t_player *g, float plane_x, float plane_y);
int				start_dir_player(t_game *var);

// PRINTABLE
int				print_error(char *str, char *color, int value_return);
void			print_error_exit(char *str, char *color, int exit_code);
void			print_message(char *str, char *color);

// TEXTURE
int				load_texture(t_game *var, t_tex *tex, char *img_path);
int				init_texture(t_game *var);
void			get_texture(t_map *map, int i);
int				parse_texture(t_map *map);
int				open_texture(t_map *map);

// UTILS - PRECISANDO DE ARQUIVO

// VALIDATION
int				array_length(char **s);
int				is_valid_args(int argc, char **argv);
int				above_and_below(t_map **map, int i, int j, int x);
int				check_surroundings(t_map **map, int i, int j);

#endif