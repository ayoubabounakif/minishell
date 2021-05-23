/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:06:43 by aabounak          #+#    #+#             */
/*   Updated: 2020/12/15 12:55:46 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*g_alloc[400];
int		g_all = 0;

void	to_free(void)
{
	int		i;

	i = -1;
	while (++i < g_all)
		free(g_alloc[i]);
}

void	*ft_malloc(size_t n)
{
	void	*tmp;

	if (!(tmp = malloc(n)))
		return (NULL);
	g_alloc[g_all] = tmp;
	g_all++;
	return (tmp);
}
