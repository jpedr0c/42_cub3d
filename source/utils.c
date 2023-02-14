#include "../include/cub3d.h"

int	array_length(char **s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}