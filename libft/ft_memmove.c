/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:56:20 by aabounak          #+#    #+#             */
/*   Updated: 2019/10/25 15:36:44 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tdst;
	const char	*tsrc;
	char		*enddst;
	const char	*endsrc;

	tdst = dst;
	tsrc = src;
	enddst = tdst + (len - 1);
	endsrc = tsrc + (len - 1);
	if (src == 0 && dst == 0)
		return (0);
	if ((tdst < tsrc) || (dst == src && len == 1))
		return (ft_memcpy(dst, src, len));
	while (len-- > 0)
		*enddst-- = *endsrc--;
	return (dst);
}
