/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:15:10 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/26 14:15:10 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main (int argc, char **argv)
{
    t_vars *var;

    if (!is_valid_args(argc, argv))
        return (1);
    var = (t_vars *)malloc(sizeof(t_vars));
    var->map = (t_map *)malloc(sizeof(t_map));
    init_map(map);
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