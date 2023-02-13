/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom_sings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/01/27 23:38:14 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/27 23:38:14 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_split(char **splited)
{
	int	i;

	i = -1;
	while (splited[++i])
		free(splited[i]);
	free(splited);
	splited = NULL;
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

void	free_struct_var(t_vars *var)
{
	free(var->map);
	free(var->ray);
	free(var);
	var = NULL;
}

int	free_with_exit(t_map *map, int back)
{
	free_split(map->buffer);
	free(map->we);
	free(map->so);
	free(map->no);
	free(map->ea);
	map = NULL;
	exit(back);
}

void	free_all(t_vars *var)
{
	mlx_destroy_image(var->mlx, var->img.img);
	mlx_destroy_image(var->mlx, var->tex[TEX_NO].img.img);
	mlx_destroy_image(var->mlx, var->tex[TEX_SO].img.img);
	mlx_destroy_image(var->mlx, var->tex[TEX_WE].img.img);
	mlx_destroy_image(var->mlx, var->tex[TEX_EA].img.img);
	mlx_destroy_window(var->mlx, var->win);
	free_struct_var(var);
	var = NULL;
}
