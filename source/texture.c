/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:05:54 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/07 14:26:36 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

int	load_texture(t_vars *var, t_tex *tex, char *img_path)
{
	if (img_path == NULL)
		return (print_error("Path to image is null", REDN, 0));
	tex->img.img = mlx_xpm_file_to_image(var->mlx, img_path, &tex->w, &tex->h);
	if (tex->img.img == NULL)
		return (print_error("Failed to convert xpm file to image", REDN, 0));
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bpp, &tex->img.line_len, &tex->img.endian);
	if (tex->img.addr == NULL)
		return (print_error("Failed to get image address", REDN, 0));
	return (1);
}

int	init_texture(t_vars *var)
{
	if (!load_texture(var, &var->tex[TEX_NO], var->map->no)
		|| !load_texture(var, &var->tex[TEX_SO], var->map->so)
		|| !load_texture(var, &var->tex[TEX_WE], var->map->we)
		|| !load_texture(var, &var->tex[TEX_EA], var->map->ea))
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
	fd[4] = open(map->s, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1 || fd[3] == -1 || fd[4] == -1)
		return (0);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	close(fd[4]);
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

int get_texture_WE_EA(t_map **map, int i)
{
	char	*aux;

	if (!ft_strncmp((*map)->buffer[i], "WE", 2))
	{
		if ((*map)->we)
			print_error("Duplicated texture WE\n", REDN, 0);
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->we = aux;
		return (1);
	}
	else if (!ft_strncmp((*map)->buffer[i], "EA", 2))
	{
		if ((*map)->ea)
			print_error("Duplicated texture EA\n", REDN, 0);
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->ea = aux;
		return (1);
	}
	return (0);
}

int get_texture_NO_SO(t_map **map, int i)
{
	char	*aux;

	if (!ft_strncmp((*map)->buffer[i], "NO", 2))
	{
		if ((*map)->no)
			print_error("Duplicated texture NO\n", REDN, 0);
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->no = aux;
	}
	else if (!ft_strncmp((*map)->buffer[i], "SO", 2))
	{
		if ((*map)->so)
			print_error("Duplicated texture SO\n", REDN, 0);
		aux = ft_substr((*map)->buffer[i], 3, ft_strlen((*map)->buffer[i]));
		(*map)->so = aux;
	}
	else if (get_texture_WE_EA(map, i))
		return (1);
	else
		return (0);
}

int parse_texture(t_map *map)
{
    int i;

    i = -1;
    while (map->buffer[++i] && is_filled_map(map))
    {
        if ((ft_strncmp(map->buffer[*i], "\n", 1) == 0
			|| ft_strncmp(map->buffer[*i], "\0", 1) == 0))
		    break;
    }
    if (!map->no || !map->so || !map->we || !map->ea || !map->s || !map->frgb || !map->crgb)
        return (print_error("Missing texture\n", REDN, 0));
    if (open_texture(map) == 0)
        return (print_error("Invalid texture\n", REDN, 0));
    map->aux = i;
    return (i);
}
