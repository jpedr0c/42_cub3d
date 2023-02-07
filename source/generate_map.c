/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/01/27 13:49:44 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/27 13:49:44 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	read_map(t_map *map, char *str)
{
	char	*aux;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		print_error("It's not possible to open file", REDN, 0);
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
	int i;

	i = 0;
	while ((*map)->buffer[(*map)->index])
	{
		if (ft_strncmp((*map)->buffer[(*map)->index], "\0", 1) != 0)
			break ;
		(*map)->index++;
	}
	while ((*map)->buffer[(*map)->index] && (*map)->index < (*map)->lines)
	{
		if (!*(*map)->buffer[(*map)->index])
			break ;
		(*map)->map[i++] = ft_substr((*map)->buffer[(*map)->index],
			0, ft_strlen((*map)->buffer[(*map->index)]));
		(*map)->index++;
	}
	(*map)->map[i] == NULL;
}

int	fill_buffer(char *file, int lines, t_map *map)
{
	char *str;
	int	fd;
	int	i;

	i = -1;
	map->buffer = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!map->buffer)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (++i < lines)
	{
		str = get_next_line(fd);
		map->buffer[i] = ft_substr(str, 0, ft_strlen(str) - 1);
		free(str);
	}
	map->buffer[i] = NULL;
	close(fd);
	return (1);
}

int	init_parser(t_map *map, char *str)
{
	if (map->lines == 0)
		return (print_error("Empty map\n", REDN, 0));
	if (map->lines == 0)
		return (print_error("Empty map\n", REDN, 0));
	if (parse_texture(map) < 0)
		return (0);
	if (parse_map(&map) != 0)
		return (free_struct_map(map, 0));
	if (last_map_check(&map) != 0)
		return (free_struct_map(map, 0));
	if (map->p_pos[0] == -1 || map->p_pos[1] == -1)
		free_struct_map(map, 0);
	return (1);
}