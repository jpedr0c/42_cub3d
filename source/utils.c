/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/01/26 14:41:23 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/26 14:41:23 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ignore_spaces(char *line, int i)
{
	if (!line)
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	array_length(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	print_message(char *str, char *color)
{
	char	*reset_color;

	reset_color = DEFAULT;
	printf("%s%s%s\n", color, str, reset_color);
}
