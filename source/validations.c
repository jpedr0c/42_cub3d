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

int	is_digit_args(char **s)
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