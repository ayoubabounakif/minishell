/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rstr_methods2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:43:18 by khafni            #+#    #+#             */
/*   Updated: 2021/09/15 18:58:06 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	rstr_lookup(t_rstr haystack, char *needle)
{
	int	i;
	int	j;

	(void)needle;
	(void)haystack;
	i = 0;
	j = 0;
	while (i < haystack->len)
	{
		j = 0;
		while (j < haystack->len && needle[j])
		{	
			if (((i + j) > haystack->len)
				|| (rstr_get(haystack, i + j) != needle[j]))
				break ;
			if ((size_t)j == (ft_strlen(needle) - 1))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	cstr_lookup(char *haystack, char *needle)
{
	t_rstr	rs;
	int		i;

	rs = cstr_to_rstr(haystack);
	i = rstr_lookup(rs, needle);
	rstr_destroy(rs);
	return (i);
}

void	rstr_destroyer(t_rstr r1, t_rstr r2)
{
	rstr_destroy(r1);
	rstr_destroy(r2);
}

int	is_cstrs_equal(char *s1, char *s2)
{
	t_rstr	r1;
	t_rstr	r2;
	int		i;

	r1 = cstr_to_rstr(s1);
	r2 = cstr_to_rstr(s2);
	if (!r1 || !r2 || (r1->len != r2->len))
	{
		rstr_destroyer(r1, r2);
		return (0);
	}
	i = 0;
	while (i < r1->len)
	{
		if (rstr_get(r1, i) != rstr_get(r2, i))
		{
			rstr_destroyer(r1, r2);
			return (0);
		}
		i++;
	}
	rstr_destroyer(r1, r2);
	return (1);
}
