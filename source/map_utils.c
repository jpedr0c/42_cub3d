/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:27:46 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 11:27:46 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_existing_texture(char *direction)
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

void	ignore_empty_lines(t_map **map)
{
	while ((*map)->buffer[(*map)->aux] && !(*map)->buffer[(*map)->aux][0])
	{
		(*map)->aux++;
	}
	(*map)->index = (*map)->aux;
}

int	ignore_spaces(char *line, int i)
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
