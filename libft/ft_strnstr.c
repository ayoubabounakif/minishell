/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:49:43 by aabounak          #+#    #+#             */
/*   Updated: 2019/10/24 15:52:15 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		needlelen;

	i = 0;
	needlelen = ft_strlen(needle);
	if ((!*needle && !len) || !*needle)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	if (ft_strlen(haystack) < needlelen)
		return (0);
	while (i <= len)
	{
		if ((!(ft_strncmp((haystack + i), needle, needlelen))))
			return ((char *)(haystack + i));
		len--;
		i++;
	}
	return (0);
}
