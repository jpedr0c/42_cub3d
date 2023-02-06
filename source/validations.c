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

	i = skip_spaces(line, 0);
	if (index == 0 || index == (*map)->height - 1)
		return (check_top_and_bot(line));
	else if (*line && (line[i] != '1' || line[ft_strlen(line) - 1] != '1'))
		return (error_ret("Error\nMap not closed by 1's\n", 1));
	while (*line && line[++i] != '\n' && line[i] != '\0')
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == 'N'
				|| line[i] == ' ' || line[i] == 'E'
				|| line[i] == 'W' || line[i] == 'S'
				|| line[i] == 'C' || line[i] == 'O'))
			return (error_ret("Error\nInvalid character on the map\n", 1));
		else
		{
			if (counter(line[i], map) != 0)
				return (error_ret("Error\nToo many player spawns\n", 1));
		}
	}
	return (0);
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
		while (++j < map->columns)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
				(*map)->count++;
		}
	}
	if ((*map)->count > 1)
		return (print_error("Invalid map. There is more than one direction",
				REDN, 0));
	return (1);
}
