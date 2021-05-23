/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:04:17 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 12:48:41 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*sp = NULL; /* the start position of the string */

char	*ft_strtok(char * str, char *delimiters)
{
    int		i = 0;
    int		len = ft_strlen(delimiters);
 
    /* check in the delimiters */
    if (len == 0)
        printf("delimiters are empty\n");
 
    /* if the original string has nothing left */
    if (!str && !sp)
    	return NULL;
 
    /* initialize the sp during the first call */
    if (str && !sp)
        sp = str;
 
    /* find the start of the substring, skip delimiters */
    char*	p_start = sp;
    while (1)
	{
		for (i = 0; i < len; i++)
		{
            if (*p_start == delimiters[i])
			{
            	p_start ++;
            	break ;
            }
        }
        if (i == len)
		{
			sp = p_start;
			break ;
        }
    }
 
    /* return NULL if nothing left */
    if (*sp == '\0')
	{
		sp = NULL;
		return sp;
    }

	/* find the end of the substring, and
		replace the delimiter with null */
	while (*sp != '\0')
	{
		for (i = 0; i < len; i++)
		{
			if (*sp == delimiters[i])
			{
            	*sp = '\0';
            	break ;
			}
		}
        sp ++;
        if (i < len)
            break ;
    }
    return p_start;
}

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
		// if (str[i] == '\\')
			// i++;
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
