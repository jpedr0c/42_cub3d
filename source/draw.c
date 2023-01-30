/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:19:53 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/30 14:19:53 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

void    init_ray(t_vars *var, t_ray *ray, int x)
{
    ray->cam_x = (2 * x) / (float)WIDTH - 1;
    ray->dir_x = var->g.dir_x + var->g.plane_x * ray->cam_x;
    ray->dir_y = var->g.dir_y + var->g.plane_y * ray->cam_x;
    ray->map_x = (int)var->g.pos_y;
    if (ray->dir_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = // fabs;
    if (ray->dir_y == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_y = //fabs;
    ray->hit = 0;
    ray->hit_door = 0;
}

void    draw(t_vars *var)
{
    var->door_hit[X] = -1;
    var->door_hit[Y] = -1;
    ft_bzero(var->img.addr, WIN_H * WIN_W * (var->img.bpp / 8));
    // TODO: Função de Raycast das paredes
    // TODO: Função de Raycast sprite
    // TODO: Função de colocar um ponto no centro da tela
    mlx_put_image_to_window(var->mlx, var->win, var->img.img, 0, 0);
    // TODO: Função do minimap
    // TODO: Função para mostrar na tela os controles

}