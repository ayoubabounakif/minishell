/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_proccessing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:26:33 by khafni            #+#    #+#             */
/*   Updated: 2021/09/14 18:28:17 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	raqfos_helper1(t_raqfos *raqfos)
{
	raqfos->conti = 0;
	if (raqfos->sq_state && raqfos->mask[raqfos->i] == '\'')
	{
		raqfos->sq_state = 0;
		raqfos->i++;
		raqfos->conti = 1;
		return ;
	}
	else if (raqfos->dq_state && raqfos->mask[raqfos->i] == '"')
	{
		raqfos->dq_state = 0;
		raqfos->i++;
		raqfos->conti = 1;
		return ;
	}
}

void	raqfos_helper2(t_raqfos *raqfos)
{
	if (!raqfos->sq_state && !raqfos->dq_state
		&& raqfos->mask[raqfos->i] == '"')
	{
		raqfos->dq_state = 1;
		raqfos->i++;
		raqfos->conti = 1;
		return ;
	}
	if (!raqfos->sq_state && !raqfos->dq_state
		&& raqfos->mask[raqfos->i] == '\'')
	{
		raqfos->sq_state = 1;
		raqfos->i++;
		raqfos->conti = 1;
		return ;
	}
	if (raqfos->sq_state && raqfos->mask[raqfos->i] != '\'')
		rstr_add(raqfos->rs, raqfos->a_token[raqfos->i]);
	if (raqfos->dq_state && raqfos->mask[raqfos->i] != '"')
		rstr_add(raqfos->rs, raqfos->a_token[raqfos->i]);
	if (!raqfos->sq_state && !raqfos->dq_state
		&& raqfos->mask[raqfos->i] != '\'' && raqfos->mask[raqfos->i] != '"')
		rstr_add(raqfos->rs, raqfos->a_token[raqfos->i]);
}

void	remove_all_quotes_from_one_string(char *a_token, char **r_str)
{
	t_raqfos	raqfos;

	raqfos.mask = get_mask(a_token);
	raqfos.sq_state = 0;
	raqfos.dq_state = 0;
	raqfos.i = 0;
	raqfos.rs = rstr_create(0);
	raqfos.a_token = a_token;
	raqfos.r_str = r_str;
	raqfos.conti = 0;
	while (raqfos.mask[raqfos.i])
	{
		raqfos_helper1(&raqfos);
		if (!raqfos.conti)
			raqfos_helper2(&raqfos);
		if (!raqfos.conti)
			raqfos.i++;
	}
	free(*(raqfos.r_str));
	*(raqfos.r_str) = rstr_to_cstr(raqfos.rs);
	rstr_destroy(raqfos.rs);
	free(raqfos.mask);
}

void	remove_quotes_from_tokens(void *data)
{
	t_commands_table	cmd;
	int					i;
	char				*value;

	i = 0;
	cmd = data;
	while (i < cmd->tokens->len)
	{
		value = cmd->tokens_simpl[i];
		remove_all_quotes_from_one_string(cmd->tokens_simpl[i],
			&(cmd->tokens_simpl[i]));
		i++;
	}
}

void	remove_quotes(t_dlist parsed_line)
{
	dlist_move_cursor_to_head(parsed_line);
	while (parsed_line->cursor_n != parsed_line->sentinel)
	{
		remove_quotes_from_tokens(parsed_line->cursor_n->value);
		dlist_move_cursor_to_next(parsed_line);
	}
}
