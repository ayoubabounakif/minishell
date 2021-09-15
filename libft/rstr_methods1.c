/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rstr_methods1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:43:08 by khafni            #+#    #+#             */
/*   Updated: 2021/09/15 18:46:45 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*rstr_to_cstr(t_rstr rs)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(rs->len + 1);
	while (i < rs->len)
	{
		str[i] = rs->data[i];
		i++;
	}
	str[rs->len] = '\0';
	return (str);
}

char	rstr_get(t_rstr rs, int index)
{
	if (index < 0 || index >= rs->len)
		return (-42);
	return (*(rs->data + index));
}

t_rstr	cstr_to_rstr(char *cstr)
{
	t_rstr	rs;
	int		i;

	if (!cstr)
		return (NULL);
	i = 0;
	rs = rstr_create(0);
	while (cstr[i])
	{
		rstr_add(rs, cstr[i]);
		i++;
	}
	return (rs);
}

void	cstr_to_rstr_without_n_rs(char *src, t_rstr dst)
{
	int		i;

	rstr_clear(dst);
	i = 0;
	while (src[i])
	{
		rstr_add(dst, src[i]);
		i++;
	}
}

t_rstr	rstr_clone(t_rstr src)
{
	t_rstr	dst;
	int		i;

	dst = rstr_create(0);
	i = 0;
	while (i < src->len)
	{
		rstr_set(dst, i, rstr_get(src, i));
		i++;
	}
	return (dst);
}
