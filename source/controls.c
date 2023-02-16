/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:47:18 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 17:08:02 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*checks which key is currently being pressed, and moves the player forward 
or backward, based on the pressed key.
The player's movement speed is affected by whether the shift key is pressed.*/
void	vertical_player_move(int keycode, t_game *var, float speed)
{
	t_player	*p;
	char		**map;

	p = &var->p;
	map = var->map->map;
	if (var->keys.shift == 1)
		speed *= (float)2.0;
	if (keycode == KEY_W)
	{
		if (map[(int)p->pos_y][(int)(p->pos_x + p->dir_x * speed)] == FLOOR)
			p->pos_x += p->dir_x * speed;
		if (map[(int)(p->pos_y + p->dir_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y += p->dir_y * speed;
	}
	else if (keycode == KEY_S)
	{
		if (map[(int)p->pos_y][(int)(p->pos_x - p->dir_x * speed)] == FLOOR)
			p->pos_x -= p->dir_x * speed;
		if (map[(int)(p->pos_y - p->dir_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y -= p->dir_y * speed;
	}
}

/*checks which key is currently being pressed, and moves the player left or 
right, based on the pressed key.
The player's movement speed is affected by whether the shift key is pressed.*/
void	horizontal_player_move(int keycode, t_game *var, float speed)
{
	t_player	*p;
	char		**map;

	p = &var->p;
	map = var->map->map;
	if (var->keys.shift == 1)
		speed *= (float)2.0;
	if (keycode == KEY_D)
	{
		if (map[(int)p->pos_y][(int)(p->pos_x - p->plane_x * speed)] == FLOOR)
			p->pos_x -= p->plane_x * speed;
		if (map[(int)(p->pos_y - p->plane_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y -= p->plane_y * speed;
	}
	else if (keycode == KEY_A)
	{
		if (map[(int)p->pos_y][(int)(p->pos_x + p->plane_x * speed)] == FLOOR)
			p->pos_x += p->plane_x * speed;
		if (map[(int)(p->pos_y + p->plane_y * speed)][(int)p->pos_x] == FLOOR)
			p->pos_y += p->plane_y * speed;
	}
}

/*Rotates the player's direction and camera plane, based on whether the left 
or right arrow key is pressed*/
void	change_vision_player(int keycode, t_game *var, float speed)
{
	t_player	*p;
	float		old_dir_x;
	float		old_plane_x;

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

/*Detects which keys are currently being pressed, and calls corresponding
functions to move the player vertically or horizontally, or to change the
player's viewing direction, based on the pressed keys*/
void	handle_keypress(t_game *var)
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
