/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_first_sep.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:42:48 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/23 15:42:55 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_split_first_sep(char const *s, char c)
{
	char	**tab;
	char	*str;
	char	*value;

	str = (char*)s;
	if (!str)
		return (0);
	if (!(tab = ft_malloc(3 * 8)))
		return (0);
	value = ft_strchr(str, c);
	value[0] = 0;
	value++;
	tab[0] = ft_strdup(str);
	tab[1] = ft_strdup(value);
	tab[2] = 0;
	return (tab);
}
