/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:48:03 by khafni            #+#    #+#             */
/*   Updated: 2021/07/07 12:23:01 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** private struct and methods
*/

t_dlist     cmd_tables(char *parsing_text, t_dlist env_list)
{
	t_dlist     c_tables;
	t_arrptr    pls;
	t_commands_table ct = NULL;
	t_pipeline p;
	int i;

	i = 0;
	c_tables = dlist_empty_create(NULL, NULL, NULL);
	pls = get_pipelines(parsing_text);
	while (i < pls->len)
	{
		p = arrptr_get(pls, i);
		ct = cmd_table(p, env_list);
		cmd_table_fill(ct, p);
		dlist_pushback(c_tables, ct);
		i++;
	}
	arrptr_destroy(pls);
	return (c_tables);
}

void        cmd_tables_destroy(t_dlist cmd_tables_list)
{
	dlist_destroy(cmd_tables_list);
}

/*
** public struct and methods
*/

t_dlist  cmd_tables_list_(char *parsing_text, t_dlist env_list)
{
	t_dlist list_;
	t_commands_table c_tables_tmp;
	
	list_ = cmd_tables(parsing_text, env_list);
	dlist_move_cursor_to_head(list_);
	while (list_->cursor_n != list_->sentinel)
	{
		c_tables_tmp =  list_->cursor_n->value;
		list_->cursor_n->value = command_table(c_tables_tmp, env_list);
		cmd_table_destroy(c_tables_tmp); // source of the problem
		dlist_move_cursor_to_next(list_);
	}
	list_->destroy = command_table_destroy;
	return (list_);
}

void cmd_tables_list_destroy_(t_dlist cmds_array)
{
	dlist_destroy(cmds_array);
}


t_dlist      cmd_tables_list(char *parsing_text, t_dlist env_list)
{
	t_dlist tmp_list_of_command_tables_non_splitted;
	t_dlist list_of_command_tables_lists;
	t_dlist a_command_table_list;
	t_command   *cmd_tab;
	int         is_it_time_for_a_new_list;
	int         is_it_end_of_list;

	is_it_time_for_a_new_list = 0;
	is_it_end_of_list = 0;
	tmp_list_of_command_tables_non_splitted = cmd_tables_list_(parsing_text, env_list);
	list_of_command_tables_lists = dlist_empty_create(dlist_destroy, NULL, NULL);
	a_command_table_list = dlist_empty_create(command_table_destroy, NULL, NULL);
	dlist_move_cursor_to_head(tmp_list_of_command_tables_non_splitted);
	while (tmp_list_of_command_tables_non_splitted->cursor_n != tmp_list_of_command_tables_non_splitted->sentinel)
	{
		cmd_tab = tmp_list_of_command_tables_non_splitted->cursor_n->value;
		if (is_it_time_for_a_new_list)
		{
			dlist_pushback(list_of_command_tables_lists, a_command_table_list);
			a_command_table_list = dlist_empty_create(command_table_destroy, NULL, NULL);        
			is_it_time_for_a_new_list = 0;
		}
		if (is_it_end_of_list)
		{
			dlist_pushback(list_of_command_tables_lists, a_command_table_list);
			is_it_end_of_list = 0;
		}
		if (cmd_tab->is_after_p_or_sc == IS_AFTER_PIPE)
			dlist_pushback(a_command_table_list, cmd_tab);
		else if (cmd_tab->is_after_p_or_sc == IS_AFTER_SEMICOLON)
		{
			dlist_pushback(a_command_table_list, cmd_tab);
			is_it_time_for_a_new_list = 1;
		}
		else if (cmd_tab->is_after_p_or_sc == NO_PIPE_OR_SEMICOLON)
		{
			dlist_pushback(a_command_table_list, cmd_tab);
			dlist_pushback(list_of_command_tables_lists, a_command_table_list);
			is_it_end_of_list = 1;
		}
		dlist_move_cursor_to_next(tmp_list_of_command_tables_non_splitted);
	}
	//cmd_tables_list_destroy_(tmp_list_of_command_tables_non_splitted);
	return (list_of_command_tables_lists);
}

t_dlist		parse_line(char *parsing_line, t_dlist env_list)
{
	t_syx_check syx;
	t_dlist     cmd_tbs_lists;

	syx = syntax_check_create(); 
	check_pipes_n_semiclns(parsing_line, syx); 
	if (syx->is_error)
	{
		printf("%s", syx->error_message);
		syntax_destroy(syx);
		exit(1);
	}
	cmd_tbs_lists = cmd_tables_list(parsing_line, env_list);
	if (syx->is_error)
	{
		printf("%s", syx->error_message);
		syntax_destroy(syx);
		exit(1);
	}
	//syntax_destroy(syx);
	return (cmd_tbs_lists);
}