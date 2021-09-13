/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstTokenExpander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:01:20 by khafni            #+#    #+#             */
/*   Updated: 2021/09/13 17:20:15 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void token_array_changer(void *data)
{
	t_commands_table	cmd;
	t_arrptr			arr;
	int					i;

	cmd = data;
	empty_arrptr_create(free);
	i = 0;
	while(cmd->tokens_simpl[i])
	{
		arrptr_add(arr, ft_strdup(cmd->tokens_simpl[i]));
		i++;
	}
}

void	firstTokenExpander(t_dlist pDataL)
{
	dlist_move_cursor_to_head(pDataL);
	while (pDataL->cursor_n != pDataL->sentinel)
	{
		token_array_changer(pDataL->cursor_n->value);
		dlist_move_cursor_to_next(pDataL);
	}
}
