/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:04:00 by khafni            #+#    #+#             */
/*   Updated: 2021/09/11 10:04:03 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	rstrFARHelper(t_rstr rs, int *i, t_rstr haystack)
{
	rstr_add(rs, rstr_get(haystack, *i));
	(*i)++;
}

void	rstrFARHelper2(int *j, int *i)
{
	*i += *j;
	*j = 0;
}

char	*rstr_find_and_replace(t_rstr haystack, char *needle, char *new_needle)
{
	int		i;
	int		j;
	t_rstr	rs;
	char	*str;

	i = 0;
	rs = rstr_create(0);
	while (i < haystack->len)
	{
		j = 0;
		while (needle[j] && (needle[j] == rstr_get(haystack, i + j))
			&& (i + j) < haystack->len)
			j++;
		if (j == (ft_strlen(needle)))
		{	
			rstrFARHelper2(&j, &i);
			while (new_needle[j])
				rstr_add(rs, new_needle[j++]);
		}
		else
			rstrFARHelper(rs, &i, haystack);
	}
	str = rstr_to_cstr(rs);
	rstr_destroy(rs);
	return (str);
}

char	*str_find_and_replace(char *haystack, char *needle, char *new_needle)
{
	t_rstr	haystack_;
	char	*rslt;

	haystack_ = cstr_to_rstr(haystack);
	rslt = rstr_find_and_replace(haystack_, needle, new_needle);
	rstr_destroy(haystack_);
	return (rslt);
}
