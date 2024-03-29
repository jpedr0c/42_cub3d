/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:26:24 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 12:26:24 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*Calculates steps and starting distance*/
void	calculate_step_and_side(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->p.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->p.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->p.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->p.pos_y)
			* ray->delta_dist_y;
	}
}

/* Determine which wall will be hit next by the view radius (ray) in the 
simulation*/
void	detect_next_collision(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

/* Checks if it is a wall and returns true or false */
int	check_collision_wall(t_game *game, t_ray *ray)
{
	return (game->map->map[ray->map_y][ray->map_x] == WALL);
}

/*Finds out which parts of the map our beam hits and stops the algorithm 
when a wall is hit*/
void	dda(t_game *game, t_ray *ray)
{
	while (!ray->hit)
	{
		detect_next_collision(ray);
		ray->hit = check_collision_wall(game, ray);
	}
}
