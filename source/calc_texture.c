/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:17:01 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 12:17:01 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calculate_screen_line(t_ray *ray)
{
	if (!ray->side)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	calculate_texture_id(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			ray->texture_id = TEX_WE;
		else
			ray->texture_id = TEX_EA;
	}
	else
	{
		if (ray->dir_y < 0)
			ray->texture_id = TEX_NO;
		else
			ray->texture_id = TEX_SO;
	}
}

void	calculate_wall_coordinate(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->p.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = game->p.pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	calculate_texture_coordinate(t_game *game, t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * TEX_W);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
	{
		ray->tex_x = game->tex[ray->texture_id].w - ray->tex_x - 1;
	}
}

void	calculate_texture_data(t_game *game, t_ray *ray)
{
	calculate_wall_coordinate(game, ray);
	calculate_texture_coordinate(game, ray);
	ray->step = game->tex[ray->texture_id].h / (double)ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
}
