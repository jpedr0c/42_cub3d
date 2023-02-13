/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:39:45 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/13 12:00:18 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

int parse_map(t_map **map)
{
   int i;

	i = -1;
	skip_empty_lines(map);
	count_lines(map, (*map)->index);
	while ((*map)->aux <= ((*map)->lines) && (*map)->buffer[(*map)->aux] \
	 && *(*map)->buffer[(*map)->aux]) 
	{
		if (!line_handler((*map)->buffer[(*map)->aux], ++i, map))
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