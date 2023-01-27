/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:32:49 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/26 14:32:49 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/libft/include/ft_printf.h"
# include "../libraries/libft/include/get_next_line.h"
# include "../libraries/libft/include/libft.h"
# include "../libraries/minilibx_linux/mlx.h"
# include "colors.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

//CUB3D

//UTILS
void   printError(char *str, char *color, int exit_code);
int check_all_spaces(char *str);

#endif