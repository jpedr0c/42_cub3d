/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:50 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/14 17:26:32 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	if (is_valid_args(argc, argv))
		return (1);
	vars = (t_vars *)malloc(sizeof(t_vars));
	vars->map = (t_map *)malloc(sizeof(t_map));
	init_map(vars->map);
	if (read_map(vars->map, argv[1]) || init_parser(vars->map, argv[1]))
		return (1);
	print_message("Starting game 🕹️", BLUEI);
	if (init_game(vars))
		return (1);
	return (0);
}
