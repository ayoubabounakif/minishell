/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:09:00 by aabounak          #+#    #+#             */
/*   Updated: 2019/10/27 22:52:10 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	v;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	if (dst == NULL && size == 0)
		return (len);
	while (*dst != '\0' && i < size)
	{
		dst++;
		i++;
	}
	v = size - i;
	if (v == 0)
		return (i + ft_strlen(src));
	while (*src != '\0' && v != 1)
	{
		*dst++ = *src;
		v--;
		src++;
	}
	*dst = '\0';
	return (i + len);
}
