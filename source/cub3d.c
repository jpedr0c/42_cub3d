/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasilva <rasilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:50 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/16 12:22:13 by rasilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (!is_valid_args(argc, argv))
		return (1);
	game = (t_game *)malloc(sizeof(t_game));
	game->map = (t_map *)malloc(sizeof(t_map));
	init_map(game->map);
	if (!read_map(game->map, argv[1]) || !init_parser(game->map, argv[1]))
		return (1);
	print_message("Starting game 🕹️", BLUEI);
	if (init_game(game))
		return (1);
	return (0);
}
