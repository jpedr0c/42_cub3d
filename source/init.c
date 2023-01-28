/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:38:15 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/27 13:38:15 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    init_map(t_map *map)
{
    map->buffer = NULL;
    map->no = NULL;
    map->so = NULL;
    map->we = NULL;
    map->ea = NULL;
    map->door = NULL
    map->height = 0;
    map->width = 0;
    map->crgb = 0;
    map->frgb = 0;
    map->lines = 0;
    map->count = 0;
    map->sprite_cnt = 0;
    map->pos_cnt = 0;
    map->p_pos[0] = -1;
    map->p_pos[1] = -1;
    map->pos_index = -1;
    map->sprite_index = -1
}

int is_valid_map(t_map *map, char *str)
{
    if (map->lines == 0)
        return (print_error("This map is empty", 0));
    return (1);
}

int set_key_press(int keycode)
{
    if (keycode == KEY_ESC)
        //close game
    return (0);
}

int initialise_vars(t_vars *var)
{
    var->frame = -1;
    // MALLOC RAY CASTING
    return (0);
}

int init_game(t_vars *var)
{
    mlx_hook(var->win, 2, (1L << 0), KEY_PRESS, var);
    mlx_hook(var->win, 3, (1L << 1), KEY_RELEASE, var);
    mlx_hook(var->win, 17, (1L << 17), CLOSE_WIN, var);
    mlx_hook(var->win, 6, (1L << 6), MOUSE_HOOK, var);
    mlx_loop_hook(var->mlx, game_loop, var);
    mlx_loop(var->mlx);
    //FREE ALL
    return (0);
}