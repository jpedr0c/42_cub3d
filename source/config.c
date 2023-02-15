/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:02:24 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/15 12:39:30 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	initialize_vars(t_vars *vars)
{
	vars->frame = -1;
	vars->keys.w = 0;
	vars->keys.s = 0;
	vars->keys.a = 0;
	vars->keys.d = 0;
	vars->keys.right_arrow = 0;
	vars->keys.left_arrow = 0;
	vars->keys.shift = 0;
	start_dir_player(vars);
	vars->ray = (t_ray *)malloc(sizeof(t_ray));
	if (vars->ray == NULL)
		print_error_exit("Could not allocate\n", REDN, 1);
	return (0);
}

void	init_map(t_map *map)
{
	map->buffer = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->height = 0;
	map->width = 0;
	map->crgb = 0;
	map->frgb = 0;
	map->lines = 0;
	map->count = 0;
	map->p_pos[0] = -1;
	map->p_pos[1] = -1;
}

int	initialize_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bpp,
			&vars->img.line_len,
			&vars->img.endian);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "cub3D");
	if (init_texture(vars) != 0)
		return (1);
	return (0);
}

int	fill_buffer(char *file, int lines, t_map *map)
{
	int		i;
	int		fd;
	char	*s;

	i = 0;
	fd = open(file, O_RDONLY);
	s = NULL;
	if (fd < 0)
		return (1);
	map->buffer = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!map->buffer)
		return (1);
	while (i < lines)
	{
		s = get_next_line(fd);
		map->buffer[i++] = ft_substr(s, 0, ft_strlen(s) - 1);
		free(s);
	}
	map->buffer[i] = NULL;
	close(fd);
	return (0);
}
