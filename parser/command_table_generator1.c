/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_generator1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:58:19 by khafni            #+#    #+#             */
/*   Updated: 2021/09/14 17:50:41 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	cmd_tables_list_helperHelper(t_cmd_tables_list *ctl)
{
	void	**val;
	void	**val2;

	val2 = (void **)&(ctl->a_command_table_list);
	val = &(ctl->tmp_list_of_command_tables_non_splitted->cursor_n->value);
	ctl->cmd_tab = *val;
	if (ctl->is_it_time_for_a_new_list)
	{
		dlist_pushback(ctl->list_of_command_tables_lists,
			ctl->a_command_table_list);
		*val2 = dlist_empty_create(command_table_destroy, NULL, NULL);
		ctl->is_it_time_for_a_new_list = 0;
	}
	if (ctl->is_it_end_of_list)
	{
		dlist_pushback(ctl->list_of_command_tables_lists,
			ctl->a_command_table_list);
		ctl->is_it_end_of_list = 0;
	}
}

void	cmd_tables_list_helper(t_cmd_tables_list *ctl)
{
	cmd_tables_list_helperHelper(ctl);
	if (ctl->cmd_tab->is_after_p_or_sc == IS_AFTER_PIPE)
		dlist_pushback(ctl->a_command_table_list, ctl->cmd_tab);
	else if (ctl->cmd_tab->is_after_p_or_sc == IS_AFTER_SEMICOLON)
	{
		dlist_pushback(ctl->a_command_table_list, ctl->cmd_tab);
		ctl->is_it_time_for_a_new_list = 1;
	}
	else if (ctl->cmd_tab->is_after_p_or_sc == NO_PIPE_OR_SEMICOLON)
	{
		dlist_pushback(ctl->a_command_table_list, ctl->cmd_tab);
		dlist_pushback(ctl->list_of_command_tables_lists,
			ctl->a_command_table_list);
		ctl->is_it_end_of_list = 1;
	}
}

t_dlist	cmd_tables_list(char *parsing_text)
{
	t_cmd_tables_list	ctl;
	void				**v1;
	void				**v2;
	void				**v3;

	v1 = (void **)&(ctl.tmp_list_of_command_tables_non_splitted);
	v2 = (void **)&(ctl.list_of_command_tables_lists);
	v3 = (void **)&(ctl.a_command_table_list);
	ctl.is_it_time_for_a_new_list = 0;
	ctl.is_it_end_of_list = 0;
	*v1 = cmd_tables_list_(parsing_text);
	*v2 = dlist_empty_create(dlist_destroy, NULL, NULL);
	*v3 = dlist_empty_create(command_table_destroy, NULL, NULL);
	dlist_move_cursor_to_head(ctl.tmp_list_of_command_tables_non_splitted);
	while (ctl.tmp_list_of_command_tables_non_splitted->cursor_n
		!= ctl.tmp_list_of_command_tables_non_splitted->sentinel)
	{
		cmd_tables_list_helper(&ctl);
		dlist_move_cursor_to_next(ctl.tmp_list_of_command_tables_non_splitted);
	}	
	dlist_destroy(ctl.tmp_list_of_command_tables_non_splitted);
	return (ctl.list_of_command_tables_lists);
}

void	parse_line_helper(char *parsing_line, t_dlist env_list
		, t_dlist *cmd_tbs_lists)
{
	*cmd_tbs_lists = cmd_tables(parsing_line);
	expandEnvVarsInParsedData(*cmd_tbs_lists, env_list);
	firstTokenExpander(*cmd_tbs_lists);
	remove_quotes(*cmd_tbs_lists);
}
