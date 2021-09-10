/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 11:56:21 by khafni            #+#    #+#             */
/*   Updated: 2021/09/10 11:56:24 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	tokens_helper(t_pipeline pl, t_tokens tk, t_rstr tmp_str,
			t_rstr tmp_str_m)
{
	int	i;

	i = 0;
	while (pl->cmd_line_m[i])
	{
		if (pl->cmd_line_m[i] != 'W')
		{
			rstr_add(tmp_str, pl->cmd_line[i]);
			rstr_add(tmp_str_m, pl->cmd_line_m[i]);
		}
		else if (pl->cmd_line_m[i] == 'W' && tmp_str_m->len > 0)
		{
			dlist_pushback(tk->tokens, rstr_to_cstr(tmp_str));
			dlist_pushback(tk->tokens_masks, rstr_to_cstr(tmp_str_m));
			rstr_clear(tmp_str);
			rstr_clear(tmp_str_m);
		}
		i++;
	}
}

/*
** tokens take a pipeline aka a cmd_line
** and its mask and returns them as tokens so
** a further parsing on the tokens can be done
** and we can get a command table from every group
** of tokens
*/
t_tokens	tokens(t_pipeline pl)
{
	t_tokens	tk;
	t_rstr		tmp_str;
	t_rstr		tmp_str_m;
	int			i;

	tk = malloc(sizeof(struct s_tokens));
	i = 0;
	tmp_str = rstr_create(0);
	tmp_str_m = rstr_create(0);
	tk->tokens = dlist_empty_create(free, NULL, NULL);
	tk->tokens_masks = dlist_empty_create(free, NULL, NULL);
	tokens_helper(pl, tk, tmp_str, tmp_str_m);
	if (tmp_str_m->len)
	{
		dlist_pushback(tk->tokens, rstr_to_cstr(tmp_str));
		dlist_pushback(tk->tokens_masks, rstr_to_cstr(tmp_str_m));
	}
	tokens_split_w_red(tk->tokens);
	tokens_split_w_red(tk->tokens_masks);
	rstr_destroy(tmp_str);
	rstr_destroy(tmp_str_m);
	return (tk);
}

void	tokens_destroy(t_tokens tks)
{
	dlist_destroy(tks->tokens);
	dlist_destroy(tks->tokens_masks);
	free(tks);
}
