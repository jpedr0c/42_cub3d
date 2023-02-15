/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:19 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 12:43:40 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	array_length(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_valid_args(int argc, char **argv)
{
	if (argc != 2)
	{
		return (print_error("Invalid number of arguments. Use: ./cub3d map.cub",
				REDN, 1));
	}
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		return (print_error("Invalid file extension. Accepted is .cub",
				REDN, 1));
	}
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
