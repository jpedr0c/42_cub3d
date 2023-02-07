/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:47:18 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/07 18:37:23 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	vertical_player_move(int keycode, t_vars *var, float speed)
{
	t_player	*g;
	char		**map;

	g = &var->g;
	map = var->map->map;
	if (keycode == KEY_SHIFT)
		speed *= 2.00;
	else if (keycode == KEY_W)
	{
		if (map[(int)g->pos_y][(int)(g->pos_x + g->dir_x * speed)] == FLOOR)
			g->pos_x += g->dir_x * speed;
		if (map[(int)(g->pos_y + g->dir_y * speed)][(int)g->pos_x] == FLOOR)
			g->pos_y += g->dir_y * speed;
	}
	else if (keycode == KEY_S)
	{
		if (map[(int)g->pos_y][(int)(g->pos_x - g->dir_x * speed)] == FLOOR)
			g->pos_x -= g->dir_x * speed;
		if (map[(int)(g->pos_y - g->dir_y * speed)][(int)g->pos_x] == FLOOR)
			g->pos_y -= g->dir_y * speed;
	}
}

void	horizontal_player_move(int keycode, t_vars *var, float speed)
{
	t_player	*g;
	char		**map;

	g = &var->g;
	map = var->map->map;
	if (keycode == KEY_SHIFT)
		speed *= (float)2;
	else if (keycode == KEY_A)
	{
		if (map[(int)g->pos_y][(int)(g->pos_x + g->plane_x * speed)] == FLOOR)
			g->pos_x += g->plane_x * speed;
		if (map[(int)(g->pos_y + g->plane_y * speed)][(int)g->pos_x] == FLOOR)
			g->pos_y += g->plane_y * speed;
	}
	else if (keycode == KEY_D)
	{
		if (map[(int)g->pos_y][(int)(g->pos_x - g->plane_x * speed)] == FLOOR)
			g->pos_x -= g->plane_x * speed;
		if (map[(int)(g->pos_y - g->plane_y * speed)][(int)g->pos_x] == FLOOR)
			g->pos_y -= g->plane_y * speed;
	}
}

void	change_vision_player(int keycode, t_vars *var, float speed)
{
	t_player	*g;
	float		old_dir_x;
	float		old_plane_x;

	g = &var->g;
	if (keycode == ARROW_LEFT)
	{
		old_dir_x = g->dir_x;
		g->dir_x = g->dir_x * cos(-speed) - g->dir_y * sin(-speed);
		g->dir_y = g->dir_x * sin(-speed) + g->dir_y * cos(-speed);
		old_plane_x = g->plane_x;
		g->plane_x = g->plane_x * cos(-speed) - g->plane_y * sin(-speed);
		g->plane_y = old_plane_x * sin(-speed) + g->plane_y * cos(-speed);
	}
	else if (keycode == ARROW_RIGHT)
	{
		old_dir_x = g->dir_x;
		g->dir_x = g->dir_x * cos(speed) - g->dir_y * sin(speed);
		g->dir_y = g->dir_x * sin(speed) + g->dir_y * cos(speed);
		old_plane_x = g->plane_x;
		g->plane_x = g->plane_x * cos(speed) - g->plane_y * sin(speed);
		g->plane_y = old_plane_x * sin(speed) + g->plane_y * cos(speed);
	}
}

int	handle_keypress(int keycode, t_vars *var)
{
	if (keycode == KEY_ESC)
		close_window(var);
	else if (keycode == KEY_W || keycode == KEY_S)
		vertical_player_move(keycode, var, 0.05);
	else if (keycode == KEY_A || keycode == KEY_D)
		horizontal_player_move(keycode, var, 0.05);
	else if (keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		change_vision_player(keycode, var, 0.05);
	// else if (keycode == KEY_SHIFT)
	//     // TODO: Aumentar velocidade
	return (0);
}
