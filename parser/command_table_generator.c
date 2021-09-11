/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:48:03 by khafni            #+#    #+#             */
/*   Updated: 2021/09/11 14:08:56 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** private struct and methods
*/

t_dlist	cmd_tables(char *parsing_text)
{
	t_dlist				c_tables;
	t_arrptr			pls;
	t_commands_table	ct;
	t_pipeline			p;
	int					i;

	ct = NULL;
	i = 0;
	c_tables = dlist_empty_create(cmd_table_destroy, NULL, NULL);
	pls = get_pipelines(parsing_text);
	while (i < pls->len)
	{
		p = arrptr_get(pls, i);
		ct = cmd_table(p);
		cmd_table_fill(ct);
		dlist_pushback(c_tables, ct);
		i++;
	}
	arrptr_destroy(pls);
	return (c_tables);
}

void	cmd_tables_destroy(t_dlist cmd_tables_list)
{
	dlist_destroy(cmd_tables_list);
}

/*
** public struct and methods
*/

t_dlist	cmd_tables_list_(char *parsing_text)
{
	t_dlist				list_;
	t_commands_table	c_tables_tmp;

	list_ = cmd_tables(parsing_text);
	dlist_move_cursor_to_head(list_);
	while (list_->cursor_n != list_->sentinel)
	{
		c_tables_tmp = list_->cursor_n->value;
		list_->cursor_n->value = command_table(c_tables_tmp);
		dlist_move_cursor_to_next(list_);
	}
	list_->destroy = command_table_destroy;
	return (list_);
}

void	cmd_tables_list_destroy_(t_dlist cmds_array)
{
	dlist_destroy(cmds_array);
}
