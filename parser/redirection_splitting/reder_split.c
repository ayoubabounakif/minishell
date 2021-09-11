/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reder_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:54:58 by khafni            #+#    #+#             */
/*   Updated: 2021/09/11 13:55:00 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_red_cmd_non_split(char *token_, char *mask)
{
	char	*token;	
	int		i;
	int		r;
	int		al;

	i = 0;
	r = 0;
	al = 0;
	token = (char *)token_;
	while (token[i])
	{
		if (mask[i] == '>' || mask[i] == '<')
			r = 1;
		else
			al = 1;
		i++;
	}
	if (r == 1 && al == 1)
		return (1);
	else
		return (0);
}

void	split_token_w_red_help(char *token, int *i, t_arrptr arr)
{
	t_rstr	rs;

	rs = rstr_create(1);
	while (token[*i] && (token[*i] == '>' || token[*i] == '<'))
		rstr_add(rs, token[(*i)++]);
	if (rs->len)
		arrptr_add(arr, rstr_to_cstr(rs));
	rstr_clear(rs);
	while (token[*i] && (token[*i] != '>' && token[*i] != '<'))
		rstr_add(rs, token[(*i)++]);
	if (rs->len)
		arrptr_add(arr, rstr_to_cstr(rs));
	rstr_destroy(rs);
}

void	split_token_w_red_helper(t_split_token_w_red *stwk)
{
	while (stwk->token[stwk->i])
	{
		if (stwk->mask[stwk->i] != '>' && stwk->mask[stwk->i] != '<')
		{
			rstr_add(stwk->rs, stwk->token[stwk->i]);
		}
		else if (stwk->mask[stwk->i] == '>' || stwk->mask[stwk->i] == '<')
		{
			if (stwk->rs->len)
				arrptr_add(stwk->arr, rstr_to_cstr(stwk->rs));
			split_token_w_red_help(stwk->token, &(stwk->i), stwk->arr);
			rstr_clear(stwk->rs);
			continue ;
		}
		stwk->i++;
	}
}

t_arrptr	split_token_w_red(char *token)
{
	t_split_token_w_red	stwk;

	stwk.token = token;
	stwk.mask = get_mask(token);
	stwk.i = 0;
	stwk.rs = rstr_create(0);
	stwk.arr = empty_arrptr_create(free);
	split_token_w_red_helper(&stwk);
	free(stwk.mask);
	rstr_destroy(stwk.rs);
	return (stwk.arr);
}
