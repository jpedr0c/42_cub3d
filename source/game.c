/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:32 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 10:20:34 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press_hook(int keycode, t_game *var)
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

int	key_release_hook(int keycode, t_game *var)
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

int	close_window(t_game *game)
{
	free_all(game);
	print_message("Good bye 👋", PURPLEI);
	exit(0);
	return (0);
}

int	game_loop(t_game *game)
{
	if (++game->frame >= 60)
		game->frame = 0;
	handle_keypress(game);
	draw(game);
	return (0);
}

int	init_game(t_game *game)
{
	if (initialize_game(game))
	{
		free_all(game);
		print_error_exit("Unable to allocate variables", REDN, 1);
	}
	if (initialize_mlx(game) != 0)
		return (1);
	mlx_hook(game->win, 2, (1L << 0), key_press_hook, game);
	mlx_hook(game->win, 3, (1L << 1), key_release_hook, game);
	mlx_hook(game->win, 17, (1L << 17), close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	free_all(game);
	return (0);
}
