/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_first_sep.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:42:48 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/15 19:06:46 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_first_sep(char const *s, char c)
{
	char	**tab;
	char	*str;
	char	*value;

	str = (char *)s;
	if (!str)
		return (0);
	tab = ft_malloc(3 * 8);
	value = ft_strchr(str, c);
	value[0] = 0;
	value++;
	tab[0] = ft_strdup(str);
	tab[1] = ft_strdup(value);
	tab[2] = 0;
	return (tab);
}
