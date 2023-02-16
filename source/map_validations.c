/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:20:43 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 11:20:43 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	is_filled_map(const t_map *map)
{
	return (!map->no || !map->so || !map->we || !map->ea || !map->frgb
		|| !map->crgb);
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

	i = ignore_spaces(line, 0);
	if (index == 0 || index == (*map)->height - 1)
		return (verify_border(line));
	else if (*line && (line[i] != '1' || line[ft_strlen(line) - 1] != '1'))
		return (print_error("Map not closed by 1's\n", REDN, 1));
	while (*line && line[++i] != '\n' && line[i] != '\0')
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == 'N'
				|| line[i] == ' ' || line[i] == 'E' || line[i] == 'W'
				|| line[i] == 'S'))
			return (print_error("Invalid character on the map\n", REDN, 1));
		else
		{
			if (counter(line[i], map))
				return (print_error("Too many player spawns\n", REDN, 1));
		}
	}
	return (0);
}

int	last_map_check(t_map **map)
{
	int	i;
	int	j;

	i = 0;
	while ((*map)->map[++i])
	{
		j = ignore_spaces((*map)->map[i], 0);
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
