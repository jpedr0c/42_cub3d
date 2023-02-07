/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:09:56 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/03 14:09:56 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int process_colors(t_map **map, int i, char **ptr)
{
    int tmp[3];

    if (array_length(ptr) != 3)
        return (0);
    if (is_array_digit(ptr) == 1)
        return (0);
    tmp[0] = ft_atoi(ptr[0]);
    tmp[1] = ft_atoi(ptr[1]);
    tmp[2] = ft_atoi(ptr[2]);
    if (tmp[0] < 0 || tmp[0] > 256 || tmp[1] < 0 || tmp[1] > 256 || tmp[2] < 0 || tmp[2] > 256)
        return (0);
    if (ft_strncmp((*map)->buffer[i], "F", 1) == 0)
    {
        if ((*map)->frgb != 0)
            return (print_error("Duplicate Colors\n", REDN, 0));
        (*map)->frgb = create_rgba(tmp[0], tmp[1], tmp[2], 0);
    }
    else
    {
        if ((*map)->crgb != 0)
            return (print_error("Duplicate Colors\n", REDN, 0));
        (*map)->crgb = create_rgba(tmp[0], tmp[1], tmp[2], 0);
    }
    return (1);
}

int read_color(t_map **map, int i)
{
    char *aux;
    char **splited;

    if (ft_strncmp((*map)->buffer[i], "F", 1) == 0
        || ft_strncmp((*map)->buffer[i], "C", 1) == 0)
    {
        aux = ft_substr((*map)->buffer[i], 2, ft_strlen((*map)->buffer[i]) - 1);
        splited = ft_split(aux, ',');
        free(aux);
        if (process_colors(map, i, splited) == 1)
            return (print_error("Invalid Colour\n", REDN, 0));
    }
    else
        return (0);
    if (splited)
        free_split(splited);
    return (1);
}
