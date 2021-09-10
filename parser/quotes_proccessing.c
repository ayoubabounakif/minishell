/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_proccessing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:27:03 by khafni            #+#    #+#             */
/*   Updated: 2021/09/10 13:27:04 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*remove_quotes_from_stringImproved(char *a_token, char type_of_quotes)
{
	char	*mask;
	t_rstr	tmp_str;
	int		i;
	char	*r_str;

	i = 0;
	mask = get_mask(a_token);
	tmp_str = rstr_create(0);
	while (a_token[i])
	{
		if (mask[i] != type_of_quotes)
			rstr_add(tmp_str, a_token[i]);
		i++;
	}
	r_str = rstr_to_cstr(tmp_str);
	rstr_destroy(tmp_str);
	free(a_token);
	free(mask);
	return (r_str);
}

void	process_tokens_from_quotes(t_tokens tks)
{
	char	*v;
	char	*v_m;

	dlist_move_cursor_to_head(tks->tokens);
	while (tks->tokens->cursor_n != tks->tokens->sentinel)
	{
		v = tks->tokens->cursor_n->value;
		if (ft_strchr(v, '"'))
			tks->tokens->cursor_n->value = remove_quotes_from_stringImproved(v,
					'"');
		if (ft_strchr(v, '\''))
			tks->tokens->cursor_n->value = remove_quotes_from_stringImproved(v,
					'\'');
		dlist_move_cursor_to_next(tks->tokens);
	}
}

void	remove_quotes_from_tokens(void *data)
{
	t_commands_table	cmd;
	int					i;
	char				*mask;
	char				*value;

	i = 0;
	cmd = data;
	while (i < cmd->tokens->len)
	{
		value = cmd->tokens_simpl[i];
		mask = get_mask(value);
		if (ft_strchr(mask, '"'))
			cmd->tokens_simpl[i] = remove_quotes_from_stringImproved(value,
					'"');
		if (ft_strchr(mask, '\''))
			cmd->tokens_simpl[i] = remove_quotes_from_stringImproved(value,
					'\'');
		free(mask);
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
