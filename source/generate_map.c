/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:36 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 17:07:31 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	read_map(t_map *map, char *str)
{
	char	*aux;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (print_error("Not possible! Archive not exist or invalid map",
				REDN, 0));
	aux = get_next_line(fd);
	while (aux)
	{
		++map->lines;
		free(aux);
		aux = get_next_line(fd);
	}
	close(fd);
	return (1);
}

void	fill_map(t_map **map)
{
	int	i;

	i = 0;
	while ((*map)->buffer[(*map)->index] && (*map)->index < (*map)->lines)
	{
		if (*(*map)->buffer[(*map)->index])
		{
			(*map)->map[i++] = ft_substr((*map)->buffer[(*map)->index], 0,
					ft_strlen((*map)->buffer[(*map)->index]));
			(*map)->index++;
		}
		else
			break ;
	}
	(*map)->map[i] = NULL;
}

void	check_width(t_map **map)
{
	if ((int)ft_strlen((*map)->buffer[(*map)->aux]) > (*map)->width)
		(*map)->width = (int)ft_strlen((*map)->buffer[(*map)->aux]);
}

int	parse_map(t_map **map)
{
	int	i;

	i = -1;
	ignore_empty_lines(map);
	count_lines(map, (*map)->index);
	while ((*map)->aux <= ((*map)->lines) && (*map)->buffer[(*map)->aux]
		&& *(*map)->buffer[(*map)->aux])
	{
		if (line_handler((*map)->buffer[(*map)->aux], ++i, map))
			return (0);
		check_width(map);
		(*map)->aux++;
	}
	(*map)->map = (char **)ft_calloc((i + 2), sizeof(char *));
	if (!(*map)->map)
		return (0);
	fill_map(map);
	return (1);
}

int	init_parser(t_map *map, char *str)
{
	if (!map->lines)
		return (print_error("Empty map", REDN, 0));
	if (!fill_buffer(str, map->lines, map))
		return (print_error("Fatal error", REDN, 0));
	if (parse_texture(map) < 0)
		return (0);
	if (!parse_map(&map))
		return (free_map_exit(map, 1));
	if (last_map_check(&map) != 0)
		return (free_map_exit(map, 1));
	if (map->p_pos[0] == -1 || map->p_pos[1] == -1)
	{
		print_message("No player spawn", REDN);
		free_map_exit(map, 1);
	}
	return (1);
}
