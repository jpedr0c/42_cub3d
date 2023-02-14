#include "../include/cub3d.h"

/* draw crosshair on screen center */
void	draw_square(t_vars *vars)
{
	int		side_len;
	int		coords[2];
	float	x;
	float	y;

	side_len = 7;
	coords[0] = HEIGHT / 2 - side_len / 2;
	coords[1] = WIDTH / 2 - side_len / 2;
	y = 0;
	while (y < side_len)
	{
		x = 0;
		while (x < side_len)
		{
			img_pixel_put(&vars->img, coords[1] + x, coords[0] + y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

/* draw all on screen */
void	draw(t_vars *vars)
{
	ft_bzero(vars->img.addr, HEIGHT * WIDTH * (vars->img.bpp / 8));
	raycast_wall(vars);
	draw_square(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

void	draw_ver_line(t_vars *vars, int x, t_ray *ray)
{
	int		y;
	int		color;
	t_tex	*tex;

	tex = &vars->tex[ray->texture_id];
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < ray->draw_start)
			img_pixel_put(&vars->img, WIDTH - 1 - x, y, vars->map->crgb);
		if (y >= ray->draw_start && y <= ray->draw_end)
		{
			ray->tex_y = (int)ray->tex_pos & (tex->h - 1);
			ray->tex_pos += ray->step;
			color = get_pixel_color(&tex->img, ray->tex_x, ray->tex_y);
			img_paste_pixel(&vars->img, WIDTH - 1 - x, y, color);
		}
		if (y > ray->draw_end)
			img_pixel_put(&vars->img, WIDTH - 1 - x, y, vars->map->frgb);
	}
}

void	init_step_and_sidedist(t_vars *vars, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (vars->p.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - vars->p.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (vars->p.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - vars->p.pos_y)
			* ray->delta_dist_y;
	}
}

void	set_cam_x(t_ray *ray, int x, int win_w)
{
	ray->cam_x = (2 * x) / (float)win_w - 1;
}

void	set_ray_directions(t_vars *vars, t_ray *ray)
{
	ray->dir_x = vars->p.dir_x + vars->p.plane_x * ray->cam_x;
	ray->dir_y = vars->p.dir_y + vars->p.plane_y * ray->cam_x;
}

void	set_ray_map_pos(t_vars *vars, t_ray *ray)
{
	ray->map_x = (int)vars->p.pos_x;
	ray->map_y = (int)vars->p.pos_y;
}

void	set_ray_delta_dist(t_ray *ray)
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

void	init_ray(t_vars *vars, t_ray *ray, int x)
{
	set_cam_x(ray, x, WIDTH);
	set_ray_directions(vars, ray);
	set_ray_map_pos(vars, ray);
	set_ray_delta_dist(ray);
	ray->hit = 0;
}

int	get_pixel_color(t_img *img, int x, int y)
{
	int		color;
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

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
		img->addr[pixel + 3] = (color)&0xFF;
	}
	else if (img->endian == 0)
	{
		img->addr[pixel + 0] = (color)&0xFF;
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

static void	update_side_distance(t_ray *ray)
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

static int	is_wall_hit(t_vars *vars, t_ray *ray)
{
	return (vars->map->map[ray->map_y][ray->map_x] == WALL);
}

void	dda(t_vars *vars, t_ray *ray)
{
	while (!ray->hit)
	{
		update_side_distance(ray);
		ray->hit = is_wall_hit(vars, ray);
	}
}

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

static void	calculate_wall_x(t_vars *vars, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = vars->p.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = vars->p.pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

static void	calculate_tex_x(t_vars *vars, t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * TEX_W);
	if ((ray->side == 0 && ray->dir_x > 0) ||
		(ray->side == 1 && ray->dir_y < 0))
	{
		ray->tex_x = vars->tex[ray->texture_id].w - ray->tex_x - 1;
	}
}

static void	calculate_tex_step_and_pos(t_vars *vars, t_ray *ray)
{
	ray->step = vars->tex[ray->texture_id].h / (double)ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
}

void	calculate_texture_data(t_vars *vars, t_ray *ray)
{
	calculate_wall_x(vars, ray);
	calculate_tex_x(vars, ray);
	calculate_tex_step_and_pos(vars, ray);
}

void	raycast_wall(t_vars *vars)
{
	t_ray	*ray;
	int		x;

	ray = vars->ray;
	x = -1;
	while (++x < WIDTH)
	{
		init_ray(vars, ray, x);
		init_step_and_sidedist(vars, ray);
		dda(vars, ray);
		calculate_screen_line(ray);
		calculate_texture_id(ray);
		calculate_texture_data(vars, ray);
		draw_ver_line(vars, x, ray);
		ray->z_buffer[x] = ray->perp_wall_dist;
	}
}
