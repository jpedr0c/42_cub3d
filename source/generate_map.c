/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:49:44 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/27 13:49:44 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int read_map(t_map *map, char *str)
{
    char *aux;
    int fd;

    fd = open(str, O_RDONLY);
    if (fd < 0)
        print_error("It's not possible to open file", REDN, 0)
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
