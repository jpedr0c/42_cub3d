/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:07:03 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 10:20:34 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	int	pixel;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return ;
	pixel = (y * img->line_len) + (x * (img->bpp / 8));
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
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return ;
	dst = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)dst = pixel;
}

void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		color;
	t_tex	*tex;

	tex = &game->tex[ray->texture_id];
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < ray->draw_start)
			img_pixel_put(&game->img, WIDTH - 1 - x, y, game->map->crgb);
		if (y >= ray->draw_start && y <= ray->draw_end)
		{
			ray->tex_y = (int)ray->tex_pos & (tex->h - 1);
			ray->tex_pos += ray->step;
			color = get_pixel_color(&tex->img, ray->tex_x, ray->tex_y);
			img_paste_pixel(&game->img, WIDTH - 1 - x, y, color);
		}
		if (y > ray->draw_end)
			img_pixel_put(&game->img, WIDTH - 1 - x, y, game->map->frgb);
	}
}

void	raycast_wall(t_game *game)
{
	t_ray	*ray;
	int		x;

	ray = game->ray;
	x = -1;
	while (++x < WIDTH)
	{
		init_ray(game, ray, x);
		calculate_step_and_side(game, ray);
		dda(game, ray);
		calculate_screen_line(ray);
		calculate_texture_id(ray);
		calculate_texture_data(game, ray);
		draw_vertical_line(game, ray, x);
		ray->z_buffer[x] = ray->perp_wall_dist;
	}
}

/* draw crosshair on screen center */
void	draw_square(t_game *game)
{
	int		coords[2];
	float	x;
	float	y;

	coords[0] = HEIGHT / 2 - 7 / 2;
	coords[1] = WIDTH / 2 - 7 / 2;
	y = 0;
	while (y < 7)
	{
		x = 0;
		while (x < 7)
		{
			img_pixel_put(&game->img, coords[1] + x, coords[0] + y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

/* draw all on screen */
void	draw(t_game *game)
{
	ft_bzero(game->img.addr, HEIGHT * WIDTH * (game->img.bpp / 8));
	raycast_wall(game);
	draw_square(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
