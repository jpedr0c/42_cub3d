/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:15:30 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/03 14:15:30 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

void	count_lines(t_map **map, int i)
{
	while ((*map)->buffer[i] && (*map)->buffer[i])
	{
		// IF sugerido pelo COPILOTO
		if ((*map)->buffer[i][0] == '1' || (*map)->buffer[i][0] == ' ')
			(*map)->height++;
		i++;
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
				REDN, 0));
	}
	return (1);
}

int	line_handler(char *line, int index, t_map **map)
{
	int	i;

	i = ignore_spaces(line, 0);
	if (index == 0 || index == (*map)->height - 1)
		return (verify_border(line));
	else if (*line && (line[i] != '1' || line[ft_strlen(line) - 1] != '1'))
		return (print_error("Map not closed by 1's\n", REDN, 0));
	while (*line && line[++i] != '\n' && line[i])
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == 'N'
				|| line[i] == ' ' || line[i] == 'E'
				|| line[i] == 'W' || line[i] == 'S'))
			return (print_error("Invalid character on the map\n", REDN, 0));
		else
		{
			if (!is_valid_direction((*map)))
				return (print_error("Too many player spawns\n", REDN, 0));
		}
	}
	return (1);
}

int	is_valid_args(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("Invalid number of arguments. Usage: ./cub3d map.cub",
			REDN, 0);
		return (0);
	}
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		print_error("Invalid file extension. Accepted extension is .cub", REDN,
			0);
		return (0);
	}
	return (1);
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
			if (!ft_isdigit(s[i][j]))
				return (0);
	}
	return (1);
}

int is_filled_map(const t_map *map)
{
    return (map->no || map->so || map->we || map->ea || map->frgb || map->crgb || map->pos_index != -1 || map->sprite_cnt != -1);
}

int	is_valid_map(t_map *map, char *str)
{
	(void)str;
	if (map->lines == 0)
		return (print_error("This map is empty", REDN, 0));
	return (1);
}

int	is_valid_direction(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->lines)
	{
		j = -1;
		while (++j < map->height)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'E' || map->map[i][j] == 'W')
				map->count++;
		}
	}
	if (map->count > 1)
		return (print_error("Invalid map. There is more than one direction",
				REDN, 0));
	return (1);
}

int	above_and_below(t_map **map, int i, int j, int x)
{
	int og;
	char	*tmp;

	og = j;
	if (i >= array_length((*map)->map) || i <= 0)
		return (0);
	tmp = (*map)->map[i];
	while (j < x)
	{
		if (tmp[j] != '1' && tmp[j] != ' ')
			return (0);
		j++;
	}
	if (j > og)
		return (j);
	return (1);
}

int	check_surroundings(t_map **map, int i, int j)
{
	int x;
	int ret;
	int ret2;

	x = j;
	while ((*map)->map[i][x] == ' ')
		x++;
	ret = above_and_below(map, i + 1, j, x);
	ret2 = above_and_below(map, i - 1, j, x);
	if (ret == 0 || ret2 == 0)
		return (0);
	if (x > 1)
		return (x);
	return (j);
}

int last_map_check(t_map **map)
{
	int	i;
	int	j;

	i = 0;
	while ((*map)->map[++i])
	{
		j = ignore_spaces((*map)->map[i], 0);
		while ((*map)->map[i][++j] != '\n' && (*map)->map[i][j])
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
				if (j == 0)
					return (print_error("Map isn't closed by wall\n", REDN, 0));
			}
		}
	}
	return (1);
}