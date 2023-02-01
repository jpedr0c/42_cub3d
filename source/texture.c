/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:05:54 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/01 18:06:46 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

void	set_texture_id(t_ray *ray)
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

void    calculate_texture_data(t_vars *var, t_ray *ray)
{
    if (ray->side == 0)
        ray->wall_x = var->g.pos_y + ray->perp_wall_dist * ray->dir_y;
    else
        ray->wall_x = var->g.pos_x + ray->perp_wall_dist * ray->dir_x;
    ray->wall_x -= floor((ray->wall_x));
    ray->tex_x = (int)(ray->wall_x * (float)TEX_W);
    if (ray->side == 0 && ray->dir_x > 0)
        ray->tex_x = var->tex[ray->texture_id].w - ray->tex_x - 1;
    if (ray->side == 1 && ray->dir_y < 0)
        ray->tex_x = var->tex[ray->texture_id].w - ray->tex_x - 1;
    ray->step = 1.0 * var->tex[ray->texture_id].h / ray->line_height;
    ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * ray->step;
}
