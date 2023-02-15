/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:36 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 11:53:18 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	read_map(t_map *map, char *str)
{
	char	*aux;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (print_error("It's not possible to open file", REDN, 1));
	aux = get_next_line(fd);
	while (aux)
	{
		++map->lines;
		free(aux);
		aux = get_next_line(fd);
	}
	close(fd);
	return (0);
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
			return (1);
		check_width(map);
		(*map)->aux++;
	}
	(*map)->map = (char **)ft_calloc((i + 2), sizeof(char *));
	if (!(*map)->map)
		return (1);
	fill_map(map);
	return (0);
}

int	init_parser(t_map *map, char *str)
{
	if (map->lines == 0)
		return (print_error("Empty map", REDN, 1));
	if (fill_buffer(str, map->lines, map) < 0)
		return (print_error("Fatal error", REDN, 1));
	if (parse_texture(map) < 0)
		return (1);
	if (parse_map(&map) != 0)
		return (free_map(map, 1));
	if (last_map_check(&map) != 0)
		return (free_map(map, 1));
	if (map->p_pos[0] == -1 || map->p_pos[1] == -1)
		free_map(map, 1);
	return (0);
}
