/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom_sings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:41 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 10:20:34 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	split = NULL;
}

void	free_map(t_map *map)
{
	free_split(map->map);
	free_split(map->buffer);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free(map);
	map = NULL;
}

void	free_all(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_image(game->mlx, game->tex[TEX_NO].img.img);
	mlx_destroy_image(game->mlx, game->tex[TEX_SO].img.img);
	mlx_destroy_image(game->mlx, game->tex[TEX_WE].img.img);
	mlx_destroy_image(game->mlx, game->tex[TEX_EA].img.img);
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->map);
	free(game->ray);
	free(game);
	game = NULL;
}

int	free_map_exit(t_map *map, int ret)
{
	free_split(map->buffer);
	free(map->we);
	free(map->so);
	free(map->no);
	free(map->ea);
	map = NULL;
	exit(ret);
}
