/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:06:43 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/16 14:10:21 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*g_alloc[100000];
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

	tmp = malloc(n);
	if (!tmp)
		return (NULL);
	g_alloc[g_all] = tmp;
	g_all++;
	return (tmp);
}
