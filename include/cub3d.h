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

# define BUFFER_SIZE 42
# define WIDTH 1280
# define WIDTH 720
# define TEX 64
# define FLOOR '0'
# define WALL '1'

# ifdef OSX
#  define KEY_ESC 53
#  define KEY_MINUS 27
#  define KEY_PLUS 24
#  define ARROW_UP 126
#  define ARROW_DOWN 125
#  define ARROW_LEFT 123
#  define ARROW_RIGHT 124
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_P 35
#  define KEY_E 14
#  define KEY_C 8
#  define KEY_SHIFT 257
# else
#  ifndef LINUX
#   define LINUX
#  endif
#  define KEY_ESC 65307
#  define KEY_MINUS 45
#  define KEY_PLUS 61
#  define ARROW_UP 65362
#  define ARROW_DOWN 65364
#  define ARROW_LEFT 65361
#  define ARROW_RIGHT 65363
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_P 112
#  define KEY_E 101
#  define KEY_C 99
#  define KEY_SHIFT 65505
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
    char        *door;
    int         width;
    int         height;
    int         frgb;
    int         crgb;
    int         aux;
    int         lines;
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
}

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

typedef struct s_sprite_utl
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
}   t_sprite_utl


//CUB3D
int main (int argc, char **argv);

// CONTROLS
void    vertical_player_move(int keycode, t_vars *var, float speed);
void    horizontal_player_move(int keycode, t_vars *var, float speed);
void    change_vision_player(int keycode, t_vars *var, float speed);
void    handle_keypress(int keycode, t_vars *var);


// DRAW
void    init_ray(t_vars *var, t_ray *ray, int x);
void    draw(t_vars *var);


// ERROR
int    print_error(char *str, char *color, int value_return);
void    print_error_exit(char *str, char *color, int exit_code);


// FREEDOM_SINGS
void    free_split(char **splited);
void    free_map(t_map *map);
void    free_struct(t_vars *var);
void    free_all(t_vars *var);


// GENERATE_MAP
int read_map(t_map *map, char *str);


// INIT
int     close_window(t_vars *var);
int     game_loop(t_vars *var);
void    init_map(t_map *map);
int     initialize_vars(t_vars *var);
int     inilialize_mlx(t_vars *var);
int     init_game(t_vars *var);


// UTILS
int     is_valid_args(int argc, char **argv);
int     is_valid_map(t_map *map, char *str);
void    print_message(char *str, char *color);


#endif