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
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	free_split(map->map);
	free_split(map->buffer);
	if (map->sprites)
	{
		while (map->sprites[++i])
			free_split(map->sprites[i]);
		free(map->sprites);
	}
	i = -1;
	while (++i <= map->sprite_cnt)
		free(map->spaux[i].type);
	free(map->sprite);
	free(map->spaux);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free(map);
}

void	free_struct_var(t_vars *var)
{
	free(var->sprite);
	free(var->ray);
	free(var);
}

int	free_struct_map(t_map *map, int back)
{
	free_split(map->buffer);
	free(map->we);
	free(map->so);
	free(map->no);
	free(map->ea);
	exit(back);
}

void	free_all(t_vars *var)
{
	int	i;
	int	j;

	mlx_destroy_image(var->mlx, var->img.img);
	mlx_destroy_image(var->mlx, var->tex[TEX_NO].img.img);
	mlx_destroy_image(var->mlx, var->tex[TEX_SO].img.img);
	mlx_destroy_image(var->mlx, var->tex[TEX_WE].img.img);
	mlx_destroy_image(var->mlx, var->tex[TEX_EA].img.img);
	i = -1;
	while (var->sprite != NULL && var->sprite[++i] != NULL)
	{
		j = -1;
		while (var->sprite[i][++j] != NULL)
		{
			mlx_destroy_image(var->mlx, var->sprite[i][j]->img.img);
			free(var->sprite[i][j]);
		}
		free(var->sprite[i]);
	}
	mlx_destroy_window(var->mlx, var->win);
	free_struct_var(var);
}
