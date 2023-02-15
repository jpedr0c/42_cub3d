/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:07:13 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 12:52:07 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_pixel_color(t_img *img, int x, int y)
{
	int		color;
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

int	read_colors(t_map **map, int i)
{
	char	*aux;
	char	**split;

	if (ft_strncmp((*map)->buffer[i], "F", 1) == 0
		|| ft_strncmp((*map)->buffer[i], "C", 1) == 0)
	{
		aux = ft_substr((*map)->buffer[i], 2, ft_strlen((*map)->buffer[i]) - 1);
		split = ft_split(ft_substr((*map)->buffer[i], 2,
					ft_strlen((*map)->buffer[i]) - 1), ',');
		free(aux);
		if (process_colors(map, i, split) == 1)
			return (print_error("Invalid color", REDN, 1));
	}
	else
		return (1);
	if (split)
		free_split(split);
	return (0);
}
// static int	read_colors(t_map **map, int i)
// {
// 	char	**split;

// 	if (ft_strncmp((*map)->buffer[i], "F", 1) == 0
// 		|| ft_strncmp((*map)->buffer[i], "C", 1) == 0)
// 	{
// 		split = ft_split(ft_substr((*map)->buffer[i], 2,
					// ft_strlen((*map)->buffer[i]) - 1), ',');
// 		if (process_colour(map, i, ft_split(ft_substr((*map)->buffer[i], 2,
							// ft_strlen((*map)->buffer[i]) - 1), ',')) == 1)
// 			return (print_error("Invalid color", REDN, 1));
// 		free_split(split);
// 	}
// 	else
// 		return (1);
// 	return (0);
// }

int	process_colors(t_map **map, int i, char **sp)
{
	int	tmp[3];

	if (array_length(sp) != 3)
		return (1);
	if (is_array_digit(sp) == 1)
		return (2);
	tmp[0] = ft_atoi(sp[0]);
	tmp[1] = ft_atoi(sp[1]);
	tmp[2] = ft_atoi(sp[2]);
	if (tmp[0] < 0 || tmp[0] > 256 || tmp[1] < 0 || tmp[1] > 256 || tmp[2] < 0
		|| tmp[2] > 256)
		return (3);
	if (ft_strncmp((*map)->buffer[i], "F", 1) == 0)
	{
		if ((*map)->frgb != 0)
			return (print_error("Duplicated color", REDN, 1));
		(*map)->frgb = create_rgba(0, tmp[0], tmp[1], tmp[2]);
	}
	else
	{
		if ((*map)->crgb != 0)
			return (print_error("Duplicated color", REDN, 1));
		(*map)->crgb = create_rgba(0, tmp[0], tmp[1], tmp[2]);
	}
	return (0);
}
