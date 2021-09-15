/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 11:32:00 by khafni            #+#    #+#             */
/*   Updated: 2021/09/15 16:25:54 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*print_the_env_var(char *token, char *token_mask, int i)
{
	t_rstr	rs;
	int		s_envpos;
	char	*r_str;

	rs = rstr_create(0);
	rstr_add(rs, '$');
	s_envpos = i;
	i++;
	while (token_mask[i] && token_mask[i] == 'V')
	{
		rstr_add(rs, token[i]);
		i++;
	}
	r_str = rstr_to_cstr(rs);
	rstr_destroy(rs);
	return (r_str);
}

void	find_replace_env_vars_in_a_token_helperh1(t_find_replace_env *fre)
{
	if (fre->is_key_found)
	{
		if (!fre->r_str)
			fre->r_str = str_find_and_replace(fre->token,
					fre->tmp, fre->is_key_found);
		else
			fre->r_str = str_find_and_replace(fre->r_str,
					fre->tmp, fre->is_key_found);
	}
	else
	{
		if (!fre->r_str)
			fre->r_str = str_find_and_replace(fre->token,
					fre->tmp, "");
		else
			fre->r_str = str_find_and_replace(fre->r_str,
					fre->tmp, "");
	}
}

void	find_replace_env_vars_in_a_token_helper(t_find_replace_env *fre)
{
	while (fre->token[fre->i])
	{
		if (fre->token_mask[fre->i] == '$'
			&& !ft_strnstr(fre->token + fre->i, "$?", 2))
		{
			fre->tmp = print_the_env_var(fre->token, fre->token_mask, fre->i);
			fre->is_key_found = find_envv_akey_value(fre->tmp, fre->env_list);
			find_replace_env_vars_in_a_token_helperh1(fre);
			free(fre->tmp);
		}
		fre->i++;
	}
}

char	*find_replace_env_vars_in_a_token(char *token, t_dlist env_list)
{
	t_find_replace_env	fre;

	fre.i = 0;
	fre.tmp = NULL;
	fre.r_str = NULL;
	fre.env_list = env_list;
	fre.token_mask = get_mask(token);
	fre.token = token;
	find_replace_env_vars_in_a_token_helper(&fre);
	free(fre.token_mask);
	if (!fre.r_str)
		return (token);
	return (fre.r_str);
}
