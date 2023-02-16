/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:02:24 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 10:20:34 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	initialize_game(t_game *game)
{
	game->frame = -1;
	game->keys.w = 0;
	game->keys.s = 0;
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.right_arrow = 0;
	game->keys.left_arrow = 0;
	game->keys.shift = 0;
	start_dir_player(game);
	game->ray = (t_ray *)malloc(sizeof(t_ray));
	if (game->ray == NULL)
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

int	initialize_mlx(t_game *game)
{
	game->mlx = mlx_init();
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bpp,
			&game->img.line_len,
			&game->img.endian);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (init_texture(game) != 0)
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
