/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom_sings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:41 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 11:53:18 by jocardos         ###   ########.fr       */
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

void	free_all(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_NO].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_SO].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_WE].img.img);
	mlx_destroy_image(vars->mlx, vars->tex[TEX_EA].img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	free_split(map->map);
	free_split(map->buffer);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free(map);
	map = NULL;
	free(vars->ray);
	free(vars);
	vars = NULL;
}

int	free_map(t_map *map, int ret)
{
	free_split(map->buffer);
	free(map->we);
	free(map->so);
	free(map->no);
	free(map->ea);
	map = NULL;
	exit(ret);
}
