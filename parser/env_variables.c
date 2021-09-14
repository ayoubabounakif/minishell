/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:04:00 by khafni            #+#    #+#             */
/*   Updated: 2021/09/14 18:14:31 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	rstrFARHelper(t_rstr rs, int *i, t_rstr haystack)
{
	rstr_add(rs, rstr_get(haystack, *i));
	(*i)++;
}

void	rstrFARHelper2(int *j, int *i, t_rstr rs, char *new_needle)
{
	*i += *j;
	*j = 0;
	while (new_needle[*j])
		rstr_add(rs, new_needle[(*j)++]);
}

char	*rstr_find_and_replace(t_rstr haystack, char *needle,
	char *new_needle, char *mask)
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
			&& (mask[j + i] == 'V' || mask[j + i] == '$')
			&& (i + j) < haystack->len)
			j++;
		if ((size_t)j == (ft_strlen(needle)))
		{	
			rstrFARHelper2(&j, &i, rs, new_needle);
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
	char	*mask;

	mask = get_mask(haystack);
	haystack_ = cstr_to_rstr(haystack);
	rslt = rstr_find_and_replace(haystack_, needle, new_needle, mask);
	rstr_destroy(haystack_);
	free(mask);
	free(haystack);
	return (rslt);
}
