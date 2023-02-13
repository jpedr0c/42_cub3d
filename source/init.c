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
	handle_keypress(var);
	draw(var);
	return (1);
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
	map->p_pos[0] = -1;
	map->p_pos[1] = -1;
}

int	initialize_vars(t_vars *var)
{
	var->frame = -1;
	var->keys.w = 0;
	var->keys.s = 0;
	var->keys.a = 0;
	var->keys.d = 0;
	var->keys.right_arrow = 0;
	var->keys.left_arrow = 0;
	var->keys.shift = 0;
	start_dir_player(var);
	var->ray = (t_ray *)malloc(sizeof(t_ray));
	if (!var->ray)
		print_error("Could not allocate raycasting\n", REDN, 0); 
	return (1);
}

int	inilialize_mlx(t_vars *var)
{
	var->mlx = mlx_init();
	var->img.img = mlx_new_image(var->mlx, WIDTH, HEIGHT);
	var->img.addr = mlx_get_data_addr(var->img.img,
			&var->img.bpp, &var->img.line_len, &var->img.endian);
	var->win = mlx_new_window(var->mlx, WIDTH, HEIGHT, "cub3D");
	if (!init_texture(var))
		return (0);
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
	mlx_hook(var->win, 2, (1L << 0), key_press_hook, var);
	mlx_hook(var->win, 3, (1L << 1), key_release_hook, var);
	mlx_hook(var->win, 17, (1L << 17), close_window, var);
	mlx_loop_hook(var->mlx, game_loop, var);
	mlx_loop(var->mlx);
	free_all(var);
	return (1);
}
