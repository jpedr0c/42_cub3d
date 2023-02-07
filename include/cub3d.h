/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:32:49 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/26 14:32:49 by jocardos         ###   ########.fr       */
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
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 1280
# define HEIGHT 720
# define TEX 64
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
#endif

# ifdef __linux__
enum e_keycode
{
    KEY_ESC = 65307,
    KEY_MINUS = 45,
    KEY_PLUS = 61,
    ARROW_UP = 65362,
    ARROW_DOWN = 65364,
    ARROW_LEFT = 65361,
    ARROW_RIGHT = 65363,
    KEY_W = 119,
    KEY_S = 115,
    KEY_A = 97,
    KEY_D = 100,
    KEY_P = 112,
    KEY_E = 101,
    KEY_C = 99,
    KEY_SHIFT = 65505
};
# else
enum e_keycode
{
    KEY_ESC = 53,
    KEY_MINUS = 27,
    KEY_PLUS = 24,
    ARROW_UP = 126,
    ARROW_DOWN = 125,
    ARROW_LEFT = 123,
    ARROW_RIGHT = 124,
    KEY_W = 13,
    KEY_S = 1,
    KEY_A = 0,
    KEY_D = 2,
    KEY_P = 35,
    KEY_E = 14,
    KEY_C = 8,
    KEY_SHIFT = 257
};
# endif

typedef struct s_sprite
{
    int     x;
    int     y;
    int     id;
}   t_sprite;

typedef struct s_spaux
{
    char    *type;
    int     *id;
}   t_spaux;

typedef struct s_map
{
    t_sprite    *sprite;
    t_spaux     *spaux;
    char        start_orientation;
    char        **map;
    char        **buffer;
    char        ***sprites;
    char        *no;
    char        *so;
    char        *we;
    char        *ea;
    int         width;
    int         height;
    int         frgb;
    int         crgb;
    int         aux;
    int         lines;
    int         index;
    int         count;
    int         sprite_cnt;
    int         sprite_index;
    int         pos_cnt;
    int         pos_index;
    float       p_pos[2];
} t_map;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
} t_img;

typedef struct s_tex
{
    t_img   img;
    int     h;
    int     w;
} t_tex;

typedef struct s_player
{
    float     pos_x;
    float     pos_y;
    float     dir_x;
    float     dir_y;
    float     plane_x;
    float     plane_y;
} t_player;

typedef struct s_ray
{
    int     map_x;
    int     map_y;
    float   cam_x;
    float   cam_y;
    float   dir_x;
    float   dir_y;
    float   side_dist_x;
    float   side_dist_y;
    float   delta_dist_x;
    float   delta_dist_y;
    float   perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     hit_door;
    int     side;
    int     line_height;
    int     draw_start;
    int     draw_end;
    int     texture_id;
    int     tex_x;
    int     tex_y;
    float   wall_x;
    float   step;
    float   tex_pos;
    float   z_buffer[WIDTH];
    int     *sprite_order;
    float   *sprite_dist;
} t_ray;

typedef struct s_vars
{
    int         frame;
    t_map       *map;
    t_player    g;
    t_img       img;
    t_tex       tex[5];
    t_tex       ***sprite;
    t_sprite    **sprites;
    void        *win;
    void        *mlx;
    int         door_hit[2];
    t_ray       *ray;
} t_vars;

typedef struct s_sprite_util
{
    float	x;
	float	y;
	float	inv_det;
	float	transform_x;
	float	transform_y;
	int		screen_x;
	int		height;
	int		draw_start_y;
	int		draw_end_y;
	int		width;
	int		draw_start_x;
	int		draw_end_x;
	int		tex_x;
	int		d;
	int		tex_y;
	int		color;
	int		id;
	int		frame;
}   t_sprite_util;


// CUB3D
int     main (int argc, char **argv);


// COLORS
int	create_rgba(int r, int g, int b, int a);
int process_colors(t_map **map, int i, char **ptr);
int read_color(t_map **map, int i);


// CONTROLS
void    vertical_player_move(int keycode, t_vars *var, float speed);
void    horizontal_player_move(int keycode, t_vars *var, float speed);
void    change_vision_player(int keycode, t_vars *var, float speed);
int     handle_keypress(int keycode, t_vars *var);


// DRAW
void    init_ray(t_vars *var, t_ray *ray, int x);
void	init_step_and_sidedist(t_vars *var, t_ray *ray);
void    check_colision_wall(t_vars *var, t_ray *ray);
void    dda(t_vars *var, t_ray *ray);
void    calculate_screen_line(t_ray *ray);
void    draw_vertical_line(t_vars *var, t_ray *ray, int w);
void	raycast_wall(t_vars *var);
void    draw(t_vars *var);


// ERROR
int     print_error(char *str, char *color, int value_return);
void    print_error_exit(char *str, char *color, int exit_code);


// FREEDOM_SINGS
void    free_split(char **splited);
void    free_map(t_map *map);
void    free_struct_var(t_vars *var);
int     free_struct_map(t_map *map, int back);
void    free_all(t_vars *var);


// GENERATE_MAP
int     read_map(t_map *map, char *str);
void	fill_map(t_map **map);
int     fill_buffer(char *file, int lines, t_map *map);
int     init_parser(t_map *map, char *str);


// INIT
int     close_window(t_vars *var);
int     game_loop(t_vars *var);
void    init_map(t_map *map);
int     initialize_vars(t_vars *var);
int     inilialize_mlx(t_vars *var);
int     init_game(t_vars *var);


// PARSER
int     parse_map(t_map **map);


// PLAYER
void    set_dir(t_player *g, int dir_x, int dir_y);
void    set_plane(t_player *g, float plane_x, float plane_y);
int     start_dir_player(t_vars *var);


// TEXTURE
int     open_texture(t_map *map);
void	set_texture_id(t_ray *ray);
void    calculate_texture_data(t_vars *var, t_ray *ray);
int     get_texture_WE_EA(t_map **map, int i);
int     get_texture_NO_SO(t_map **map, int i);
int     parse_texture(t_map *map);


// UTILS
int     ignore_spaces(char *line, int i);
int     array_length(char **s);
void    print_message(char *str, char *color);


// VALIDATION
void    count_lines(t_map **map, int i);
int     verify_border(const char *line);
int     line_handler(char *line, int index, t_map **map);
int     is_valid_args(int argc, char **argv);
int     is_array_digit(char **s);
int     is_filled_map(const t_map *map);
int     is_valid_map(t_map *map, char *str);
int     is_valid_direction(t_map *map);
int     above_and_below(t_map **map, int i, int j, int x);
int     check_surroundings(t_map **map, int i, int j);
int     last_map_check(t_map **map);


#endif