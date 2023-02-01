/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:44:14 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/01 13:47:07 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_vars	*var;

	if (!is_valid_args(argc, argv))
		return (1);
	var = (t_vars *)malloc(sizeof(t_vars));
	var->map = (t_map *)malloc(sizeof(t_map));
	init_map(var->map);
	if (!read_map(var->map, argv[1]))
		return (1);
	if (!is_valid_map(var->map, argv[1]))
		return (1);
	print_message("Starting game...", YELLOWN);
	if (!init_game(var))
		return (1);
	print_message("Quit game", YELLOWN);
	return (0);
}
