/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:19:53 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/07 14:45:37 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ray(t_vars *var, t_ray *ray, int w)
{
	ray->cam_x = (2 * w) / (float)WIDTH - 1;
	ray->dir_x = var->g.dir_x + var->g.plane_x * ray->cam_x;
	ray->dir_y = var->g.dir_y + var->g.plane_y * ray->cam_x;
	ray->map_x = (int)var->g.pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = 2.0;
	if (ray->dir_y == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_y = 2.0;
	ray->hit = 0;
	ray->hit_door = 0;
}

void	init_step_and_sidedist(t_vars *var, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (var->g.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - var->g.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (var->g.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - var->g.pos_y)
			* ray->delta_dist_x;
	}
}

int	get_pixel_color(t_img *img, int x, int y)
{
	int	color;
	char *dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	int pixel;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	pixel = (x * (img->bpp / 8) + (y * img->line_len));
	if (img->endian == 1)
	{
		img->addr[pixel + 0] = (color >> 24);
		img->addr[pixel + 1] = (color >> 16) & 0xFF;
		img->addr[pixel + 2] = (color >> 8) & 0xFF;
		img->addr[pixel + 3] = (color) & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->addr[pixel + 0] = (color) & 0xFF;
		img->addr[pixel + 1] = (color >> 8) & 0xFF;
		img->addr[pixel + 2] = (color >> 16) & 0xFF;
		img->addr[pixel + 3] = (color >> 24);
	}
}

void	img_paste_pixel(t_img *img, int x, int y, int pixel)
{
	char *dst;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	dst = img->addr + (x * (img->bpp / 8) + (y * img->line_len));
	*(unsigned int *)dst = pixel;
}

void    check_colision_wall(t_vars *var, t_ray *ray)
{
    if (var->map->map[ray->map_y][ray->map_x] == WALL)
        ray->hit = 1;
}

void    dda(t_vars *var, t_ray *ray)
{
    while (ray->hit == 0)
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
        check_colision_wall(var, ray);
    }
}

void   calculate_screen_line(t_ray *ray)
{
    if (ray->side == 0)
        ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
    else
        ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
    ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
    ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_end >= HEIGHT)
        ray->draw_end = HEIGHT - 1;
}

void    draw_vertical_line(t_vars *var, t_ray *ray, int w)
{
    int		h;
    int		color;
    t_tex	*tex;

	tex = &var->tex[ray->texture_id];
	h = -1;
	while (++h < HEIGHT)
	{
		if (y < ray->draw_start)
			// TODO: Função img_pixel_put
		if (h >= ray->draw_start && h <= ray->draw_end)
		{
			ray->tex_y = (int)ray->tex_pos & (tex->h - 1);
			ray->tex_pos += ray->step;
			// TODO: Fazer função para colocar cor no pixel
			// TODO: Função img_paste_pixel
		}
		if (h > ray->draw_end)
			;//TODO: Função img_pixel_put
	}
}

void	raycast_wall(t_vars *var)
{
	t_ray	*ray;
	int		w;

	ray = var->ray;
	w = -1;
	while (++w < WIDTH)
	{
		init_ray(var, ray, w);
		init_step_and_sidedist(var, ray);
		dda(var, ray);
		calculate_screen_line(ray);
		set_texture_id(ray);
        calculate_texture_data(var, ray);
		draw_vertical_line(var, ray, w);
		ray->z_buffer[w] = ray->perp_wall_dist;
	}
}

void	draw(t_vars *var)
{
	var->door_hit[0] = -1;
	var->door_hit[1] = -1;
	ft_bzero(var->img.addr, HEIGHT * WIDTH * (var->img.bpp / 8));
	// TODO: Função de Raycast das paredes
	// TODO: Função de colocar um quadrado no centro da tela
	mlx_put_image_to_window(var->mlx, var->win, var->img.img, 0, 0);
	// TODO: Função para mostrar na tela os controles
}
