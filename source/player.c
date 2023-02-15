/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:35:57 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 11:57:55 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_dir(t_player *p, int dir_x, int dir_y)
{
	p->dir_x = dir_x;
	p->dir_y = dir_y;
}

void	set_plane(t_player *p, float plane_x, float plane_y)
{
	p->plane_x = plane_x;
	p->plane_y = plane_y;
}

int	start_dir_player(t_vars *vars)
{
	if (vars->map->start_orientation == 'N')
	{
		set_dir(&vars->p, 0, -1);
		set_plane(&vars->p, -0.66, 0);
	}
	else if (vars->map->start_orientation == 'S')
	{
		set_dir(&vars->p, 0, 1);
		set_plane(&vars->p, 0.66, 0.0);
	}
	else if (vars->map->start_orientation == 'W')
	{
		set_dir(&vars->p, -1, 0);
		set_plane(&vars->p, 0.0, 0.66);
	}
	else if (vars->map->start_orientation == 'E')
	{
		set_dir(&vars->p, 1, 0);
		set_plane(&vars->p, 0.0, -0.66);
	}
	vars->p.pos_x = (float)vars->map->p_pos[0] + 0.5;
	vars->p.pos_y = (float)vars->map->p_pos[1] + 0.5;
	return (0);
}
