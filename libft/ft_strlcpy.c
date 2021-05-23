/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:45:45 by aabounak          #+#    #+#             */
/*   Updated: 2019/10/24 15:49:05 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *d, const char *s, size_t n)
{
	size_t		k;
	void		*dest;

	dest = d;
	k = ft_strlen(s);
	if (n == 0)
		return (k);
	if (dest == NULL)
		return (0);
	if (n)
	{
		while (n - 1 > 0 && *s)
		{
			*(unsigned char *)dest++ = *(unsigned char *)s++;
			n--;
		}
	}
	*(unsigned char *)dest = '\0';
	return (k);
}
