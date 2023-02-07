/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:39:45 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/07 11:58:07 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

int parse_map(t_map **map)
{
    int i;
    i = -1;
    while ((*map)->buffer[(*map)->aux] && (*map)->buffer[(*map)->aux][0] == '\0')
        (*map)->aux++;
    (*map)->index = (*map)->aux;
    count_lines(map, (*map)->index);
    while ((*map)->aux <= (*map)->lines && (*map)->buffer[(*map)->aux] && *(*map)->buffer[(*map)->aux])
    {
        if (!line_handler((*map)->buffer[(*map)->aux], ++i, map))
            return (0);
        if ((int)ft_strlen((*map)->buffer[(*map)->aux]) > (*map)->width)
            (*map)->width = (int)ft_strlen((*map)->buffer[(*map)->aux]);
        (*map)->aux++;
    }
    (*map)->map = (char **)ft_calloc((i + 2), sizeof(char *));
    if (!(*map)->map)
        return (0);
    fill_map(map);
    return (1);
}