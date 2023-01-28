/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:41:23 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/26 14:41:23 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int is_valid_args(int argc, char **argv)
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

void    print_error_exit(char *str, char *color, int exit_code)
{
    char *reset_color;
    reset_color = DEFAULT;
    printf("%sError\n", color);
    printf("%s%s\n", str, reset_color);
    if (exit_code == 1)
        exit(1);
}

int    print_error(char *str, char *color, int value_return)
{
    char *reset_color;
    reset_color = DEFAULT;
    printf("%sError\n", color);
    printf("%s%s\n", str, reset_color);
    return (value_return);
}

void    print_message(char *str, char *color)
{
    char *reset_color;
    reset_color = DEFAULT;
    printf("%s%s%s\n", color, str, reset_color);
}