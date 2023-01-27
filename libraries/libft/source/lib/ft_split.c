/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:21:53 by jocardos          #+#    #+#             */
/*   Updated: 2022/05/19 14:37:46 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	act;

	i = 0;
	act = 0;
	while (*str)
	{
		if (*str != c && act == 0)
		{
			act = 1;
			i++;
		}
		else if (*str == c)
			act = 0;
		str++;
	}
	return (i);
}

static char	*write_word(const char *str, int init, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - init + 1) * sizeof(char));
	while (init < end)
		word[i++] = str[init++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = write_word(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
