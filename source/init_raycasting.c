/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:10:49 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 10:20:34 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_cam_x(t_ray *ray, int x, int win_w)
{
	ray->cam_x = (2 * x) / (float)win_w - 1;
}

void	set_ray_directions(t_game *game, t_ray *ray)
{
	ray->dir_x = game->p.dir_x + game->p.plane_x * ray->cam_x;
	ray->dir_y = game->p.dir_y + game->p.plane_y * ray->cam_x;
}

void	set_ray_map_pos(t_game *game, t_ray *ray)
{
	ray->map_x = (int)game->p.pos_x;
	ray->map_y = (int)game->p.pos_y;
}

void	calculate_delta_distances(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	set_cam_x(ray, x, WIDTH);
	set_ray_directions(game, ray);
	set_ray_map_pos(game, ray);
	calculate_delta_distances(ray);
	ray->hit = 0;
}
