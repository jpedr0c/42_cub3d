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

	p = &vars->p;
	m = vars->map->map;
	if (vars->keys.shift == 1)
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

	p = &vars->p;
	m = vars->map->map;
	if (vars->keys.shift == 1)
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

	p = &vars->p;
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

int	key_press_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		close_win(vars);
	else if (keycode == KEY_W)
		vars->keys.w = 1;
	else if (keycode == KEY_A)
		vars->keys.a = 1;
	else if (keycode == KEY_S)
		vars->keys.s = 1;
	else if (keycode == KEY_D)
		vars->keys.d = 1;
	else if (keycode == KEY_RIGHT)
		vars->keys.right_arrow = 1;
	else if (keycode == KEY_LEFT)
		vars->keys.left_arrow = 1;
	else if (keycode == KEY_SHIFT)
		vars->keys.shift = 1;
	return (0);
}

int	key_relase_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		vars->keys.w = 0;
	else if (keycode == KEY_A)
		vars->keys.a = 0;
	else if (keycode == KEY_S)
		vars->keys.s = 0;
	else if (keycode == KEY_D)
		vars->keys.d = 0;
	else if (keycode == KEY_RIGHT)
		vars->keys.right_arrow = 0;
	else if (keycode == KEY_LEFT)
		vars->keys.left_arrow = 0;
	else if (keycode == KEY_SHIFT)
		vars->keys.shift = 0;
	return (0);
}

void	handle_keypress(t_vars *var)
{
	if (vars->keys.w != vars->keys.s)
	{
		if (vars->keys.w == 1)
			vertical_player_move(KEY_W, vars, 0.05);
		else if (vars->keys.s == 1)
			vertical_player_move(KEY_S, vars, 0.05);
	}
	if (vars->keys.a != vars->keys.d)
	{
		if (vars->keys.a == 1)
			horizontal_player_move(KEY_A, vars, 0.05);
		else if (vars->keys.d == 1)
			horizontal_player_move(KEY_D, vars, 0.05);
	}
	if (vars->keys.right_arrow != vars->keys.left_arrow)
	{
		if (vars->keys.right_arrow == 1)
			change_vision_player(KEY_RIGHT, vars, 0.05);
		else if (vars->keys.left_arrow == 1)
			change_vision_player(KEY_LEFT, vars, 0.05);
	}
}
