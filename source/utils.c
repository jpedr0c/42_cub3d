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

void    printError(char *str, char *color, int exit_code)
{
    char *reset_color;
    reset_color = DEFAULT;
    printf("%sError\n", color);
    printf("%s%s\n", str, reset_color);
    if (exit_code == 1)
        exit(1);
}
