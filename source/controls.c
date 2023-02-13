/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:47:18 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/13 11:29:12 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	vertical_player_move(int keycode, t_vars *var, float speed)
{
	t_player		*p;
	char	**m;

	p = &var->p;
	m = var->map->map;
	if (var->keys.shift == 1)
		speed *= (float)2.0;
	if (keycode == KEY_W)
	{
		if (m[(int)p->pos_y][(int)(p->pos_x + p->dir_x * speed)] == FLOOR)
			p->pos_x += p->dir_x * speed;
		if (m[(int)(p->pos_y + p->dir_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y += p->dir_y * speed;
	}
	else if (keycode == KEY_S)
	{
		if (m[(int)p->pos_y][(int)(p->pos_x - p->dir_x * speed)] == FLOOR)
			p->pos_x -= p->dir_x * speed;
		if (m[(int)(p->pos_y - p->dir_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y -= p->dir_y * speed;
	}
}

void	horizontal_player_move(int keycode, t_vars *var, float speed)
{
	t_player		*p;
	char	**m;

	p = &var->p;
	m = var->map->map;
	if (var->keys.shift == 1)
		speed *= (float)2.0;
	if (keycode == KEY_D)
	{
		if (m[(int)p->pos_y][(int)(p->pos_x - p->plane_x * speed)] == FLOOR)
			p->pos_x -= p->plane_x * speed;
		if (m[(int)(p->pos_y - p->plane_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y -= p->plane_y * speed;
	}
	else if (keycode == KEY_A)
	{
		if (m[(int)p->pos_y][(int)(p->pos_x + p->plane_x * speed)] == FLOOR)
			p->pos_x += p->plane_x * speed;
		if (m[(int)(p->pos_y + p->plane_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y += p->plane_y * speed;
	}
}

void	change_vision_player(int keycode, t_vars *var, float speed)
{
	t_player		*p;
	float	old_dir_x;
	float	old_plane_x;

	p = &var->p;
	if (keycode == ARROW_LEFT)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-speed) - p->dir_y * sin(-speed);
		p->dir_y = old_dir_x * sin(-speed) + p->dir_y * cos(-speed);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-speed) - p->plane_y * sin(-speed);
		p->plane_y = old_plane_x * sin(-speed) + p->plane_y * cos(-speed);
	}
	else if (keycode == ARROW_RIGHT)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
		p->dir_y = old_dir_x * sin(speed) + p->dir_y * cos(speed);
		old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(speed) - p->plane_y * sin(speed);
		p->plane_y = old_plane_x * sin(speed) + p->plane_y * cos(speed);
	}
}

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
	return (1);
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
	else if (keycode ==	ARROW_RIGHT)
		var->keys.right_arrow = 0;
	else if (keycode == ARROW_LEFT)
		var->keys.left_arrow = 0;
	else if (keycode == KEY_SHIFT)
		var->keys.shift = 0;
	return (1);
}

void	handle_keypress(t_vars *var)
{
	if (var->keys.w != var->keys.s)
	{
		if (var->keys.w == 1)
			vertical_player_move(KEY_W, var, 0.05);
		else if (var->keys.s == 1)
			vertical_player_move(KEY_S, var, 0.05);
	}
	if (var->keys.a != var->keys.d)
	{
		if (var->keys.a == 1)
			horizontal_player_move(KEY_A, var, 0.05);
		else if (var->keys.d == 1)
			horizontal_player_move(KEY_D, var, 0.05);
	}
	if (var->keys.right_arrow != var->keys.left_arrow)
	{
		if (var->keys.right_arrow == 1)
			change_vision_player(ARROW_RIGHT, var, 0.05);
		else if (var->keys.left_arrow == 1)
			change_vision_player(ARROW_LEFT, var, 0.05);
	}
}
