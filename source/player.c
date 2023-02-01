/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:54:18 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/01 19:23:52 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

void    set_dir(t_player *g, int dir_x, int dir_y)
{
    g->dir_x = dir_x;
    g->dir_y = dir_y;
}

void    set_plane(t_player *g, float plane_x, float plane_y)
{
    g->plane_x = plane_x;
    g->plane_y = plane_y;
}

int start_dir_player(t_vars *var)
{
    if (var->map->start_orientation == 'N')
    {
        set_dir(&var->g, 0, -1);
        set_plane(&var->g, -0.66, 0.0);
    }
    else if (var->map->start_orientation == 'S')
    {
        set_dir(&var->g, 0, 1);
        set_plane(&var->g, 0.66, 0.0);
    }
    else if (var->map->start_orientation == 'W')
    {
        set_dir(&var->g, -1, 0);
        set_plane(&var->g, 0.0, 0.66);
    }
    else if (var->map->start_orientation == 'E')
    {
        set_dir(&var->g, 1, 0);
        set_plane(&var->g, 0.0, -0.66);
    }
    var->g.pos_x = (float)var->map->p_pos[0] + 0.5;
    var->g.pos_y = (float)var->map->p_pos[1] + 0.5;
    return (0);
}