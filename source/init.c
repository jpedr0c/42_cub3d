/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:32 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/14 18:08:30 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(t_vars *vars)
{
	free_all(vars);
	print_message("Good bye 👋", PURPLEI);
	exit(0);
	return (0);
}

int	game_loop(t_vars *vars)
{
	if (++vars->frame >= 60)
		vars->frame = 0;
	handle_keypress(vars);
	draw(vars);
	return (0);
}

int	init_game(t_vars *vars)
{
	if (initialize_vars(vars))
	{
		free_all(vars);
		print_error_exit("Unable to allocate variables", REDN, 1);
	}
	if (initialize_mlx(vars) != 0)
		return (1);
	mlx_hook(vars->win, 2, (1L << 0), key_press_hook, vars);
	mlx_hook(vars->win, 3, (1L << 1), key_release_hook, vars);
	mlx_hook(vars->win, 17, (1L << 17), close_window, vars);
	mlx_loop_hook(vars->mlx, game_loop, vars);
	mlx_loop(vars->mlx);
	free_all(vars);
	return (0);
}
