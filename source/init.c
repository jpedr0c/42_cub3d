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

int close_window(t_vars *var)
{
    // TODO: FREE_ALL
    print_message("Quit\n", YELLOWN);
    return (exit (0));
}

int set_key_press(int keycode)
{
    if (keycode == KEY_ESC)
        //close game
    else if (keycode == KEY_W)
        // TODO: Função para andar
    else if (keycode == KEY_A)
        // TODO: Função para andar
    else if (keycode == KEY_S)
        // TODO: Função para andar
    else if (keycode == KEY_D)
        // TODO: Função para andar
    else if (keycode == KEY_RIGHT)
        // TODO: Função para andar
    else if (keycode == KEY_LEFT)
        // TODO: Função para andar
    else if (keycode == KEY_E)
        // TODO: Função para abrir a porta
    else if (keycode == KEY_C)
        // TODO: Função para lidar com o mouse
    return (0);
}

int initialize_vars(t_vars *var)
{
    var->frame = -1;
    // TODO: MALLOC RAY CASTING
    return (0);
}

int game_loop(t_vars *var)
{
    if (++var->frame >= 60)
        var->frame = 0;
    set_key_press(var);
    handle_keypress(var);
    return (0)
}

int inilialize_mlx(t_vars *var)
{
    var->mlx = mlx_init();
    // TODO: Colocar na estrutura as images
    var->win = mlx_new_window(var->mlx, WIDTH, HEIGHT, "cub3d");
    // TODO: Inicialização do minimap
    // TODO: Condição se a inicialização das texturas funcionou
    return (1);
}

void    vertical_player_move(int keycode, t_vars *var, float speed)
{
    t_player    *g;
    char        **map;

    // g = &var->g;
    map = var->map->map;
    if (keycode == KEY_SHIFT)   
        speed *= (float)2;
    else if (keycode == KEY_W)
    {
        if (map[g->pos_y][(g->pos_x + g->dir_x * speed)] == DOOR_OPEN
			|| map[g->pos_y][(g->pos_x + g->dir_x * speed)] == FLOOR)
			(float)g->pos_x += (float)g->dir_x * speed;
        if (map[g->pos_y + g->dir_y * speed][(g->pos_x)] == DOOR_OPEN
            || map[g->pos_y + g->dir_y * speed][(g->pos_x)] == FLOOR)
            (float)g->pos_y += (float)g->dir_y * speed;
    }
    else if (keycode == KEY_S)
    {
        if (map[g->pos_y][(g->pos_x - g->dir_x * speed)] == DOOR_OPEN
			|| map[g->pos_y][(g->pos_x - g->dir_x * speed)] == FLOOR)
			(float)g->pos_x -= (float)g->dir_x * speed;
        if (map[g->pos_y - g->dir_y * speed][(g->pos_x)] == DOOR_OPEN
            || map[g->pos_y - g->dir_y * speed][(g->pos_x)] == FLOOR)
            (float)g->pos_y -= (float)g->dir_y * speed;
    } 
}

void    handle_keypress(int keycode, t_vars *var)
{
    if (keycode == KEY_W || keycode == KEY_S)
        vertical_player_move(keycode, var, 0.05);
    else if (keycode == KEY_A || keycode == KEY_D)
        // TODO: Função para mover
    else if (keycode == ARROW_LEFT)
        // TODO: Função para mover
    else if (keycode == ARROW_RIGHT)
        // TODO: Função para mover
}

int init_game(t_vars *var)
{
    if (initialize_vars(var))
    {
        // TODO: FREE_ALL
        print_error_exit("Unable to allocate variables", REDN, 1);
    }
    if (!inilialize_mlx(var))
        return (0)
    mlx_hook(var->win, 2, (1L _<< 0), set_key_press, var);
    // mlx_hook(var->win, 3, (1L << 1), KEY_RELEASE, var);
    mlx_hook(var->win, 17, (1L << 17), close_window, var);
    // mlx_hook(var->win, 6, (1L << 6), MOUSE_HOOK, var);
    mlx_loop_hook(var->mlx, game_loop, var);
    mlx_loop(var->mlx);
    // TODO: FREE ALL
    return (1);
}