/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:19:53 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/13 08:12:09 by jocardos         ###   ########.fr       */
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

void    draw_vertical_line(t_vars *var, t_ray *ray, int x)
{
    int		y;
    int		color;
    t_tex	*tex;

	tex = &var->tex[ray->texture_id];
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < ray->draw_start)
			img_pixel_put(&var->img, WIDTH - 1 - x, y, var->map->crgb);
		if (y >= ray->draw_start && y <= ray->draw_end)
		{
			ray->tex_y = (int)ray->tex_pos & (tex->h - 1);
			ray->tex_pos += ray->step;
			color = get_pixel_color(&tex->img, ray->tex_x, ray->tex_y);
			img_paste_pixel(&var->img, WIDTH - 1 - x, y, color);
		}
		if (y > ray->draw_end)
			img_pixel_put(&var->img, WIDTH - 1 - x, y, var->map->frgb);
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

void	draw_square(t_vars *var)
{
	int	side_len;
	int	coords[2];
	float	x;
	float	y;

	side_len = 7;
	coords[0] = HEIGHT / 2 - side_len / 2;
	coords[1] = WIDTH / 2 - side_len / 2;

	y = -1;
	while (++y < side_len)
	{
		x = -1;
		while (++x < side_len)
			img_pixel_put(&var->img, coords[1] + x, coords[0] + y, 0xFFFFFF);
	}
}

void	draw(t_vars *var)
{
	ft_bzero(var->img.addr, HEIGHT * WIDTH * (var->img.bpp / 8));
	raycast_wall(var);
	draw_square(var);
	mlx_put_image_to_window(var->mlx, var->win, var->img.img, 0, 0);
}
