/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:57:15 by aabounak          #+#    #+#             */
/*   Updated: 2019/11/02 15:13:07 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

char	*ft_strjoin_c_beggining(char *s1, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (s1 == 0)
		return (0);
	if (!(str = (char *)malloc(ft_strlen(s1) + 1 + 1)))
		return (0);
	str[0] = c;
	while (s1[j] != '\0')
	{
		str[i] = s1[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((s1 == 0 && s2 == 0) || !s1)
		return (0);
	if (!(str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char 			*ft_strjoin_c(char *s1, char c)
{
	char	*str;
	int		i;

	i = 0;
	if (s1 == 0)
		return (0);
	if (!(str = (char *)malloc(ft_strlen(s1) + 1 + 1)))
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = c;
	str[i] = '\0';
	return (str);
}