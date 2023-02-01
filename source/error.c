/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:51:51 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/01 13:42:25 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	print_error(char *str, char *color, int value_return)
{
	char	*reset_color;

	reset_color = DEFAULT;
	printf("%sError\n", color);
	printf("%s%s\n", str, reset_color);
	return (value_return);
}

void	print_error_exit(char *str, char *color, int exit_code)
{
	char	*reset_color;

	reset_color = DEFAULT;
	printf("%sError\n", color);
	printf("%s%s\n", str, reset_color);
	if (exit_code == 1)
		exit(1);
}
