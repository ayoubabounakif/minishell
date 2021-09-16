/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:04:17 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/16 14:03:55 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		number_of_words(char *str, char c)
{
	int		nbr;
	int		i;
	int		indicator;

	nbr = 0;
	i = 0;
	indicator = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && str[i] != c)
		{
			if (indicator != 1)
			{
				nbr++;
				indicator = 1;
			}
		}
		else
			indicator = 0;
		i++;
	}
	return (nbr);
}

static int		word_size(char *str, char c)
{
	int		i;
	int		length;

	i = 0;
	length = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		length++;
		i++;
	}
	return (length);
}

static void		fill_string(char *str, char *cas, char c)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		cas[i] = str[i];
		i++;
	}
	cas[i] = '\0';
}

static char		**fill(char *str, char **tab, char c, int indicator)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (str[++i] != '\0')
		if (str[i] != c)
		{
			if (indicator != 1)
			{
				if (!(tab[++j] = ft_malloc(1 + word_size((str + i), c))))
				{
					while (j--)
						free(tab[j]);
					free(tab);
					return (0);
				}
				fill_string(str + i, tab[j], c);
				indicator = 1;
			}
		}
		else
			indicator = 0;
	return (tab);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	char	*str;
	int		indicator;

	str = (char*)s;
	indicator = 0;
	if (!str)
		return (0);
	if (!(tab = ft_malloc((number_of_words(str, c) + 1) * 8)))
		return (0);
	tab = fill(str, tab, c, indicator);
	tab[number_of_words(str, c)] = 0;
	return (tab);
}
