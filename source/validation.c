/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:19 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/14 17:08:51 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_filled_map(const t_map *map)
{
	return (!map->no || !map->so || !map->we || !map->ea || !map->frgb
		|| !map->crgb);
}

int	valid_map(char *direction)
{
	if (direction)
		return (print_error("Duplicated texture", REDN, 1));
	return (0);
}

void	count_lines(t_map **map, int index)
{
	while ((*map)->buffer[index] && *(*map)->buffer[index])
	{
		(*map)->height++;
		index++;
	}
}

int	verify_border(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (print_error("First or last line is not filled by 1's\n",
				REDN, 1));
	}
	return (0);
}

int	line_handler(char *line, int index, t_map **map)
{
	int	i;

	i = skip_spaces(line, 0);
	if (index == 0 || index == (*map)->height - 1)
		return (verify_border(line));
	else if (*line && (line[i] != '1' || line[ft_strlen(line) - 1] != '1'))
		return (print_error("Map not closed by 1's\n", REDN, 1));
	while (*line && line[++i] != '\n' && line[i] != '\0')
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == 'N'
				|| line[i] == ' ' || line[i] == 'E' || line[i] == 'W'
				|| line[i] == 'S' || line[i] == 'C' || line[i] == 'O'))
			return (print_error("Invalid character on the map\n", REDN, 1));
		else
		{
			if (counter(line[i], map) != 0)
				return (print_error("Too many player spawns\n", REDN, 1));
		}
	}
	return (0);
}

void	skip_empty_lines(t_map **map)
{
	while ((*map)->buffer[(*map)->aux] && !(*map)->buffer[(*map)->aux][0])
	{
		(*map)->aux++;
	}
	(*map)->index = (*map)->aux;
}

static int	handle_line(char *buffer, int line_index, t_map **map)
{
	if (line_handler(buffer, line_index, map) != 0)
		return (1);
	return (0);
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
	skip_empty_lines(map);
	count_lines(map, (*map)->index);
	while ((*map)->aux <= ((*map)->lines) && (*map)->buffer[(*map)->aux]
		&& *(*map)->buffer[(*map)->aux])
	{
		if (handle_line((*map)->buffer[(*map)->aux], ++i, map) != 0)
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

int	above_and_below(t_map **map, int i, int j, int x)
{
	int		og;
	char	*tmp;

	og = j;
	if (i >= array_length((*map)->map) || i <= 0)
		return (-1);
	tmp = (*map)->map[i];
	while (j < x)
	{
		if (tmp[j] != '1' && tmp[j] != ' ')
			return (-2);
		j++;
	}
	if (j > og)
		return (j);
	return (0);
}

int	check_surroundings(t_map **map, int i, int j)
{
	int	x;
	int	ret;

	x = j;
	while ((*map)->map[i][x] == ' ')
		x++;
	ret = above_and_below(map, i + 1, j, x);
	if (ret == -2)
		return (-1);
	ret = above_and_below(map, i - 1, j, x);
	if (ret == -2)
		return (-1);
	if (x > 1)
		return (x);
	return (j);
}

int	last_map_check(t_map **map)
{
	int	i;
	int	j;

	i = 0;
	while ((*map)->map[++i])
	{
		j = skip_spaces((*map)->map[i], 0);
		while ((*map)->map[i][++j] != '\n' && (*map)->map[i][j] != '\0')
		{
			if (ft_strchr("NWSE", (*map)->map[i][j]))
			{
				(*map)->p_pos[0] = (float)j;
				(*map)->p_pos[1] = (float)i;
				(*map)->start_orientation = (*map)->map[i][j];
				(*map)->map[i][j] = '0';
			}
			if ((*map)->map[i][j] == ' ')
			{
				j = check_surroundings(map, i, j);
				if (j == -1)
					return (print_error("Map isn't closed by wall\n", REDN, 1));
			}
		}
	}
	return (0);
}

int	is_array_digit(char **s)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j] != '\n' && s[i][j])
			if (ft_isdigit(s[i][j]) == 0)
				return (1);
	}
	return (0);
}

int	is_valid_args(int argc, char **argv)
{
	if (argc != 2)
	{
		return (print_error("Invalid number of arguments. Usage: ./cub3d map.cub",
							REDN,
							1));
	}
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		return (print_error("Invalid file extension. Accepted extension is .cub",
				REDN, 1));
	}
	return (0);
}

int	skip_spaces(char *line, int i)
{
	if (!line)
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	counter(char c, t_map **map)
{
	if (c == 'E' || c == 'S' || c == 'W' || c == 'N')
		(*map)->count++;
	if ((*map)->count > 1)
		return (1);
	return (0);
}
