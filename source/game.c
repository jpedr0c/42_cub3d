/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:32 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 12:05:50 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press_hook(int keycode, t_vars *var)
{
	if (keycode == KEY_ESC)
		close_window(var);
	else if (keycode == KEY_W)
		var->keys.w = 1;
	else if (keycode == KEY_A)
		var->keys.a = 1;
	else if (keycode == KEY_S)
		var->keys.s = 1;
	else if (keycode == KEY_D)
		var->keys.d = 1;
	else if (keycode == ARROW_RIGHT)
		var->keys.right_arrow = 1;
	else if (keycode == ARROW_LEFT)
		var->keys.left_arrow = 1;
	else if (keycode == KEY_SHIFT)
		var->keys.shift = 1;
	return (0);
}

int	key_release_hook(int keycode, t_vars *var)
{
	if (keycode == KEY_W)
		var->keys.w = 0;
	else if (keycode == KEY_A)
		var->keys.a = 0;
	else if (keycode == KEY_S)
		var->keys.s = 0;
	else if (keycode == KEY_D)
		var->keys.d = 0;
	else if (keycode == ARROW_RIGHT)
		var->keys.right_arrow = 0;
	else if (keycode == ARROW_LEFT)
		var->keys.left_arrow = 0;
	else if (keycode == KEY_SHIFT)
		var->keys.shift = 0;
	return (0);
}

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
