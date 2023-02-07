/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/01/27 13:38:15 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/27 13:38:15 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(t_vars *var)
{
	free_all(var);
	print_message("Quit\n", YELLOWN);
	exit(0);
	return (0);
}

int	game_loop(t_vars *var)
{
	if (++var->frame >= 60)
		var->frame = 0;
	// handle_keypress(keycode, var);
	return (0);
}

void	init_map(t_map *map)
{
	map->buffer = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
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
	map->sprite_index = -1;
}

int	initialize_vars(t_vars *var)
{
	var->frame = -1;
	start_dir_player(var);
	var->ray = (t_ray *)malloc(sizeof(t_ray));
	if (!var->ray)
		print_error("Could not allocate\n", REDN, 0); 
	return (1);
}

int	inilialize_mlx(t_vars *var)
{
	var->mlx = mlx_init();
	// TODO: Colocar na estrutura as images
	var->win = mlx_new_window(var->mlx, WIDTH, HEIGHT, "cub3d");
	// TODO: Inicialização do minimap
	// TODO: Condição se a inicialização das texturas funcionou
	return (1);
}

int	init_game(t_vars *var)
{
	if (initialize_vars(var))
	{
		free_all(var);
		print_error_exit("Unable to allocate variables", REDN, 1);
	}
	if (!inilialize_mlx(var))
		return (0);
	mlx_hook(var->win, 2, (1L << 0), handle_keypress, var);
	// mlx_hook(var->win, 3, (1L << 1), KEY_RELEASE, var);
	mlx_hook(var->win, 17, (1L << 17), close_window, var);
	// BONUS : mlx_hook(var->win, 6, (1L << 6), MOUSE_HOOK, var);
	mlx_loop_hook(var->mlx, game_loop, var);
	mlx_loop(var->mlx);
	free_all(var);
	return (1);
}
