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

int check_args(int argc, char **argv)
{
    if (argc != 2)
    {
        printError("Invalid number of arguments. Usage: ./cub3d map.cub", REDN, 0);
        return (0);
    }
    else if(ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
    {
        printError("Invalid file extension. Accepted extension is .cub", REDN, 0);
        return (0);
    }
    return (1);
}

int main (int argc, char **argv)
{
    if (!check_args(argc, argv))
        return (0);
    printf("JOGO RODANDO\n");
    return (0);
}