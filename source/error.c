/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:58 by jocardos          #+#    #+#             */
/*   Updated: 2023/02/14 17:07:00 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	print_error(char *str, char *color, int value_return)
{
	char	*reset_color;

	reset_color = DEFAULT;
	printf("%sError\n", color);
	printf("%s%s\n", str, reset_color);
	exit(value_return);
	return (value_return);
}

void	print_error_exit(char *str, char *color, int exit_code)
{
	char *reset_color;

	reset_color = DEFAULT;
	printf("%sError\n", color);
	printf("%s%s\n", str, reset_color);
	exit(exit_code);
}