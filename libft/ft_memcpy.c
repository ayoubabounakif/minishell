/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:51:35 by aabounak          #+#    #+#             */
/*   Updated: 2019/10/25 15:28:25 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tdst;
	const char	*tsrc;

	tdst = dst;
	tsrc = src;
	if (dst == src && n == 1)
		return (dst);
	if (!tsrc && !tdst)
		return (0);
	while (n > 0)
	{
		*tdst++ = *tsrc++;
		n--;
	}
	return (dst);
}
