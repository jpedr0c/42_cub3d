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

# ifdef OSX
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_P 35
#  define KEY_MINUS 27
#  define KEY_PLUS 24
#  define KEY_R 15
#  define KEY_U 32
#  define KEY_J 38
#  define KEY_I 34
#  define KEY_K 40
#  define KEY_O 31
#  define KEY_L 37
#  define KEY_E 14
#  define KEY_C 8
#  define KEY_SHIFT 257
# else
#  ifndef LINUX
#   define LINUX
#  endif
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_P 112
#  define KEY_MINUS 45
#  define KEY_PLUS 61
#  define KEY_R 114
#  define KEY_U 117
#  define KEY_J 106
#  define KEY_I 105
#  define KEY_K 107
#  define KEY_O 111
#  define KEY_L 108
#  define KEY_E 101
#  define KEY_C 99
#  define KEY_SHIFT 65505
# endif

typedef struct s_map
{
    char    **buffer;
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    char    *door;
    int     width;
    int     height;
    int     crgb;
    int     frgb;
    int     lines;
    int     count;
    int     sprite_cnt;
    int     sprite_index;
    int     pos_cnt;
    int     pos_index;
    float   p_pos[2];
} t_map;

// typedef struct s_keys
// {
//     t_bool  w;
//     t_bool  a;
//     t_bool  s;
//     t_bool  d;
//     t_bool  c;
//     t_bool  right_arrow;
//     t_bool  left_arrow;
//     t_bool  shift;
//     int     mouse_x;
//     int     prev_mouse_x;
// } t_keys;
typedef struct s_vars
{
    int     frame;
    void    *win;
    void    *mlx;

} t_vars;





//CUB3D

//UTILS
int     is_valid_args(int argc, char **argv);
void    print_error_exit(char *str, char *color, int exit_code);
int     print_error(char *str, char *color, int value_return);
void    print_message(char *str, char *color);

//GENERATE_MAP
int     read_map(t_map *map, char *str);

//INIT
void    init_map(t_map *map);
int     is_valid_map(t_map *map, char *str);

#endif