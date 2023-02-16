/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:25 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 10:20:34 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	load_texture(t_game *game, t_tex *texture, char *xpm_path)
{
	if (!xpm_path)
		return (print_error("Path to image is null", REDN, 1));
	texture->img.img = mlx_xpm_file_to_image(game->mlx, xpm_path, &texture->w,
			&texture->h);
	if (!texture->img.img)
		return (print_error("Failed to convert xpm file to image", REDN, 1));
	texture->img.addr = mlx_get_data_addr(texture->img.img, &texture->img.bpp,
			&texture->img.line_len, &texture->img.endian);
	if (!texture->img.addr)
		return (print_error("Failed to get image address", REDN, 1));
	return (0);
}

int	init_texture(t_game *game)
{
	if (!(load_texture(game, &game->tex[TEX_NO], game->map->no)
			|| load_texture(game, &game->tex[TEX_SO], game->map->so)
			|| load_texture(game, &game->tex[TEX_WE], game->map->we)
			|| load_texture(game, &game->tex[TEX_EA], game->map->ea)))
		return (0);
	return (1);
}

void	get_texture(t_map *map, int i)
{
	if (!ft_strncmp(map->buffer[i], "NO", 2))
	{
		if (!is_existing_texture(map->no))
			map->no = ft_substr(map->buffer[i], 3, ft_strlen(map->buffer[i]));
	}
	else if (!ft_strncmp(map->buffer[i], "SO", 2))
	{
		if (!is_existing_texture(map->so))
			map->so = ft_substr(map->buffer[i], 3, ft_strlen(map->buffer[i]));
	}
	else if (!ft_strncmp(map->buffer[i], "WE", 2))
	{
		if (!is_existing_texture(map->we))
			map->we = ft_substr(map->buffer[i], 3, ft_strlen(map->buffer[i]));
	}
	else if (!ft_strncmp(map->buffer[i], "EA", 2))
	{
		if (!is_existing_texture(map->ea))
			map->ea = ft_substr(map->buffer[i], 3, ft_strlen(map->buffer[i]));
	}
	else if (read_colors(&map, i) == 1)
		;
}

int	parse_texture(t_map *map)
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
	if (!map->no || !map->so || !map->we || !map->ea || !map->frgb
		|| !map->crgb)
		return (print_error("Missing texture", REDN, 1));
	if (open_texture(map) == 1)
		return (print_error("Invalid texture", REDN, 1));
	map->aux = i;
	return (i);
}

int	open_texture(t_map *map)
{
	int	fd[4];

	fd[0] = open(map->no, O_RDONLY);
	fd[1] = open(map->so, O_RDONLY);
	fd[2] = open(map->we, O_RDONLY);
	fd[3] = open(map->ea, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1 || fd[3] == -1)
		return (1);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	return (0);
}
