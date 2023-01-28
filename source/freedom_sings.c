/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom_sings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 23:38:14 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/27 23:38:14 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    free_split(char **splited)
{
    int i;

    i = -1;
    while (splited[i])
    {
        free(splited[i]);
        i++;
    }
    free(splited);
}

void    free_vars(t_vars *var)
{
    free(var->sprite);
    free(var->ray);
    free(var);
}