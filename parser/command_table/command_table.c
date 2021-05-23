/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:49:12 by khafni            #+#    #+#             */
/*   Updated: 2021/05/01 13:41:34by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_table.h"

t_commands_table	cmd_table(t_pipeline pl, char **env)
{
	t_commands_table	ct;
	
	ct = malloc(sizeof(struct s_commands_table));	
	ct->tokens_unproccessed = tokens(pl);
	ct->tokens = empty_arrptr_create(NULL);
	ct->input_files = empty_arrptr_create(NULL);
	ct->output_files = empty_arrptr_create(NULL);
	ct->append_files = empty_arrptr_create(NULL);
	ct->is_after_p_or_sc = pl->is_after_p_or_sc;
	return (ct);
}

void				cmd_table_destroy(void *cmd_tab_)
{
	t_commands_table cmd_tab;

	cmd_tab = (t_commands_table)cmd_tab_;
	
	tokens_destroy(cmd_tab->tokens_unproccessed);
	arrptr_destroy(cmd_tab->tokens);	
	arrptr_destroy(cmd_tab->input_files);	
	arrptr_destroy(cmd_tab->output_files);	
	arrptr_destroy(cmd_tab->append_files);		
	free(cmd_tab);
}

void                cmd_table_fill(t_commands_table cmdt , t_pipeline pl)
{
	cmd_table_fill_tokens(cmdt);	
	cmd_table_fill_input(cmdt);
	cmd_table_fill_output(cmdt);
	cmd_table_fill_append(cmdt);
}

int					is_token_a_r_app_file(t_commands_table cmdt)
{
	t_tokens up;		

	up = cmdt->tokens_unproccessed;	
	if (up->tokens->cursor_p == up->tokens->sentinel)
		return (0);
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (ft_strnstr((char*)(up->tokens->cursor_p->value), ">>", 2))
			return (1);	
		return (0);
	}		
	if (ft_strnstr((char*)(up->tokens->cursor_p->value), ">>", 2))
		return (1);
	return (0);
		
}

void                cmd_table_fill_append(t_commands_table cmdt)
{
	t_tokens up;

	up = cmdt->tokens_unproccessed;
	dlist_move_cursor_to_head(up->tokens);
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		if (is_token_a_r_app_file(cmdt))
			arrptr_add(cmdt->append_files, ft_strdup(up->tokens->cursor_n->value));
		dlist_move_cursor_to_next(up->tokens);
	}
}

int					is_token_a_r_o_file(t_commands_table cmdt)
{
	t_tokens up;		

	up = cmdt->tokens_unproccessed;	
	if (up->tokens->cursor_p == up->tokens->sentinel)
		return (0);
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (*(char*)(up->tokens->cursor_p->value) == '>')
			return (1);	
		return (0);
	}	
	if (*(char*)(up->tokens->cursor_p->value) == '>'
	&& !ft_strnstr((char*)(up->tokens->cursor_p->value), ">>", 2))
		return (1);
	return (0);
		
}

void                cmd_table_fill_output(t_commands_table cmdt)
{
	t_tokens up;

	up = cmdt->tokens_unproccessed;
	dlist_move_cursor_to_head(up->tokens);
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		if (is_token_a_r_o_file(cmdt))
			arrptr_add(cmdt->output_files, ft_strdup(up->tokens->cursor_n->value));
		dlist_move_cursor_to_next(up->tokens);
	}
}

int					is_token_a_r_i_file(t_commands_table cmdt)
{
	t_tokens up;		

	up = cmdt->tokens_unproccessed;	
	if (up->tokens->cursor_p == up->tokens->sentinel)
		return (0);
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (*(char*)(up->tokens->cursor_p->value) == '<')
			return (1);	
		return (0);
	}	
	if (*(char*)(up->tokens->cursor_p->value) == '<')
		return (1);
	return (0);
		
}

void                cmd_table_fill_input(t_commands_table cmdt)
{
	t_tokens up;

	up = cmdt->tokens_unproccessed;
	dlist_move_cursor_to_head(up->tokens);
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		if (is_token_a_r_i_file(cmdt))
			arrptr_add(cmdt->input_files, ft_strdup(up->tokens->cursor_n->value));
		dlist_move_cursor_to_next(up->tokens);
	}
}

int					is_normal_token(t_commands_table cmdt)
{
	t_tokens up;		

	up = cmdt->tokens_unproccessed;	
	/* if (up->tokens->cursor_p == up->tokens->sentinel)
	{
		if (*(char*)(up->tokens->cursor_n->value) == '>'
		|| *(char*)(up->tokens->cursor_n->value) == '<')
			return (0);	
		return (1);
	}	
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (*(char*)(up->tokens->cursor_p->value) == '>'
		|| *(char*)(up->tokens->cursor_p->value) == '<')
			return (0);	
		return (1);
	}	
		if ((*(char*)(up->tokens->cursor_p->value) == '>'
		|| *(char*)(up->tokens->cursor_p->value) == '<')
		|| (*(char*)(up->tokens->cursor_n->value) == '<')
		|| (*(char*)(up->tokens->cursor_n->value) == '>'))	
			return (0);
		return (1);	 */


	if (up->tokens_masks->cursor_p == up->tokens_masks->sentinel)
	{
		if (*(char*)(up->tokens_masks->cursor_n->value) == '>'
		|| *(char*)(up->tokens_masks->cursor_n->value) == '<')
			return (0);	
		return (1);
	}	
	else if (up->tokens_masks->cursor_n == up->tokens_masks->sentinel)
	{
		if (*(char*)(up->tokens_masks->cursor_p->value) == '>'
		|| *(char*)(up->tokens_masks->cursor_p->value) == '<')
			return (0);	
		return (1);
	}	
	if ((*(char*)(up->tokens_masks->cursor_p->value) == '>'
	|| *(char*)(up->tokens_masks->cursor_p->value) == '<')
	|| (*(char*)(up->tokens_masks->cursor_n->value) == '<')
	|| (*(char*)(up->tokens_masks->cursor_n->value) == '>'))	
		return (0);
	return (1);	

}

void                cmd_table_fill_tokens(t_commands_table cmdt)
{
	t_tokens up;

	up = cmdt->tokens_unproccessed;

/* 	dlist_move_cursor_to_head(up->tokens_masks);
	while (up->tokens_masks->cursor_n != up->tokens_masks->sentinel)
	{
		if (is_normal_token(cmdt))
			arrptr_add(cmdt->tokens, ft_strdup(up->tokens_masks->cursor_n->value));	
		dlist_move_cursor_to_next(up->tokens_masks);
	} */

	dlist_move_cursor_to_head(up->tokens);
	dlist_move_cursor_to_head(up->tokens_masks);
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		if (is_normal_token(cmdt))
			arrptr_add(cmdt->tokens, ft_strdup(up->tokens->cursor_n->value));	
		dlist_move_cursor_to_next(up->tokens);
		dlist_move_cursor_to_next(up->tokens_masks);

	}
}



t_command	*command_table(t_commands_table cmd)
{
	//t_commands_table cmd;
	t_command	*command;
	int			i;
		
	command = (t_command *)malloc(sizeof(t_command));
	command->tokens = malloc(sizeof(char*) * (cmd->tokens->len + 1));
	command->input_files = malloc(sizeof(char*) * (cmd->input_files->len + 1));
	command->output_files = malloc((sizeof(char*) * cmd->output_files->len + 1));
	command->append_files = malloc((sizeof(char*) * cmd->append_files->len + 1));
	i = 0;
	while (i < cmd->tokens->len)
	{
		command->tokens[i] = arrptr_get(cmd->tokens, i);
		i++;
	}
	command->tokens[i] = NULL;
	i = 0;
	while (i < cmd->input_files->len)
	{
		command->input_files[i] = arrptr_get(cmd->input_files, i);
		i++;
	}
	command->input_files[i] = NULL;
	i = 0;
	while (i < cmd->output_files->len)
	{
		command->output_files[i] = arrptr_get(cmd->output_files, i);
		i++;
	}
	command->output_files[i] = NULL;
	i = 0;
	while (i < cmd->append_files->len)
	{
		command->append_files[i] = arrptr_get(cmd->append_files, i);
		i++;
	}
	command->append_files[i] = NULL;
	command->is_after_p_or_sc = cmd->is_after_p_or_sc;
	return (command);
}

void		command_table_destroy_helper(t_command *cmd_tab)
{
	int i;

	i = 0;
	while (cmd_tab->output_files[i])
	{
		free(cmd_tab->output_files[i]);
		i++;
	}
	i = 0;
	while (cmd_tab->append_files[i])
	{
		free(cmd_tab->append_files[i]);
		i++;
	}
	free(cmd_tab->tokens);
	free(cmd_tab->input_files);
	free(cmd_tab->output_files);
	free(cmd_tab->append_files);
	free(cmd_tab);
}

void		command_table_destroy(void *cmd_tab_)
{
	int			i;
	t_command	*cmd_tab;

	cmd_tab = (t_command*)cmd_tab_;
	i = 0;
	while (cmd_tab->tokens[i])
	{
		free(cmd_tab->tokens[i]);
		i++;
	}
	i = 0;	
	while (cmd_tab->input_files[i])
	{
		free(cmd_tab->input_files[i]);
		i++;
	}
	command_table_destroy_helper(cmd_tab);
}