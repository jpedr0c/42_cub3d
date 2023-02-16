/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:35:57 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 10:20:34 by rasilva          ###   ########.fr       */
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

int	start_dir_player(t_game *game)
{
	if (game->map->start_orientation == 'N')
	{
		set_dir(&game->p, 0, -1);
		set_plane(&game->p, -0.66, 0);
	}
	else if (game->map->start_orientation == 'S')
	{
		set_dir(&game->p, 0, 1);
		set_plane(&game->p, 0.66, 0.0);
	}
	else if (game->map->start_orientation == 'W')
	{
		set_dir(&game->p, -1, 0);
		set_plane(&game->p, 0.0, 0.66);
	}
	else if (game->map->start_orientation == 'E')
	{
		set_dir(&game->p, 1, 0);
		set_plane(&game->p, 0.0, -0.66);
	}
	game->p.pos_x = (float)game->map->p_pos[0] + 0.5;
	game->p.pos_y = (float)game->map->p_pos[1] + 0.5;
	return (0);
}
