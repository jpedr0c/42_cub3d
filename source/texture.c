/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:05:54 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/13 13:38:00 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

int	load_texture(t_vars *var, t_tex *tex, char *img_path)
{
	if (!img_path)
		return (error_ret("xpm path is null", 1));
	tex->img.img = mlx_xpm_file_to_image(var->mlx, img_path,
			&tex->w, &tex->h);
	if (!tex->img.img)
		return (error_ret("failed to convert xpm file to mlx image", 1));
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (!tex->img.addr)
		return (error_ret("failed to get mlx image address", 1));
	return (0);
}

int	init_texture(t_vars *var)
{
	if (!(load_texture(var, &var->tex[TEX_NO], var->map->no)
		|| load_texture(var, &var->tex[TEX_SO], var->map->so)
		|| load_texture(var, &var->tex[TEX_WE], var->map->we)
		|| load_texture(var, &var->tex[TEX_EA], var->map->ea)))
		return (0);
	return (1);
}

int	open_texture(t_map *map)
{
	int fd[5];

	fd[0] = open(map->no, O_RDONLY);
	fd[1] = open(map->so, O_RDONLY);
	fd[2] = open(map->we, O_RDONLY);
	fd[3] = open(map->ea, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1 || fd[3] == -1)
		return (0);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	return (1);
}

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

// Serve para calcular a posição da parede que colidiu
void calculate_wall_coordinate(t_vars *vars, t_ray *ray)
{
    if (ray->side == 0)
        ray->wall_x = vars->p.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
        ray->wall_x = vars->p.pos_x + ray->perp_wall_dist * ray->dir_x;
    ray->wall_x -= floor(ray->wall_x);
}

// Calcula a coordenada X da textura que será usada para desenhar a parede
void calculate_texture_coordinate(t_vars *vars, t_ray *ray)
{
    ray->tex_x = (int)(ray->wall_x * TEX_W);
    if ((ray->side == 0 && ray->dir_x > 0) ||
		(ray->side == 1 && ray->dir_y < 0))
        ray->tex_x = vars->tex[ray->texture_id].w - ray->tex_x - 1;
}

void    calculate_texture_data(t_vars *var, t_ray *ray)
{
	calculate_wall_coordinate(var, ray);
    calculate_texture_coordinate(var, ray);
    ray->step = 1.0 * var->tex[ray->texture_id].h / ray->line_height;
    ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * ray->step;
}

int valid_map(char *direction)
{
	if (direction)
		return (error_ret("Error\nDuplicated texture\n", 1));
	return (0);
}

void	get_texture(t_map *map, int i)
{
	if (!ft_strncmp(map->buffer[i], "NO", 2))
	{
		if (!valid_map(map->no))
			map->no = ft_substr(map->buffer[i], 3, ft_strlen(map->buffer[i]));
	}
	else if (!ft_strncmp(map->buffer[i], "SO", 2))
	{
		if (!valid_map(map->so))
			map->so = ft_substr(map->buffer[i], 3, ft_strlen(map->buffer[i]));
	}
	else if (!ft_strncmp(map->buffer[i], "WE", 2))
	{
		if (!valid_map(map->we))
			map->we = ft_substr(map->buffer[i], 3, ft_strlen(map->buffer[i]));
	}
	else if (!ft_strncmp(map->buffer[i], "EA", 2))
	{
		if (!valid_map(map->ea))
			map->ea = ft_substr(map->buffer[i], 3, ft_strlen(map->buffer[i]));
	}
	else if (read_colour(&map, i) == 1)
	;
}

int parse_texture(t_map *map)
{
    int	i;

	i = -1;
	while (map->buffer[++i] && is_filled_map(map))
	{
		if ((ft_strncmp(map->buffer[i], "\n", 1) == 0
			|| ft_strncmp(map->buffer[i], "\0", 1) == 0))
			break ;
		else
			get_texture(map, i);
	}
	if (!map->no || !map->so
		|| !map->we || !map->ea || !map->frgb || !map->crgb)
		return (error_ret("Error\nMissing data on the config file",
				0));
	if (!open_texture(map))
		return (-1);
	map->aux = i;
	return (i);
}
