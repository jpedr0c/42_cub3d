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
	map->p_pos[0] = -1;
	map->p_pos[1] = -1;
}

int	initialize_vars(t_vars *var)
{
	var->frame = -1;
	vars->keys.w = 0;
	vars->keys.s = 0;
	vars->keys.a = 0;
	vars->keys.d = 0;
	vars->keys.right_arrow = 0;
	vars->keys.left_arrow = 0;
	vars->keys.shift = 0;
	start_dir_player(var);
	var->ray = (t_ray *)malloc(sizeof(t_ray));
	if (!var->ray)
		print_error("Could not allocate raycasting\n", REDN, 1); 
	return (0);
}

int	inilialize_mlx(t_vars *var)
{
	vars->mlx = mlx_init();
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bpp, &vars->img.line_len, &vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "cub3D");
	if (init_textures(vars) != 0)
		return (1);
	return (0);
}

int	init_game(t_vars *var)
{
	if (initialize_vars(var))
	{
		free_all(var);
		print_error_exit("Unable to allocate variables", REDN, 1);
	}
	if (!inilialize_mlx(var))
		return (1);
	mlx_hook(var->win, 2, (1L << 0), key_press_hook, var);
	mlx_hook(var->win, 3, (1L << 1), key_release_hook, var);
	mlx_hook(var->win, 17, (1L << 17), close_window, var);
	mlx_loop_hook(var->mlx, game_loop, var);
	mlx_loop(var->mlx);
	free_all(var);
	return (0);
}
