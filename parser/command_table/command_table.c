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

t_redir_file redir_file(char *file_name, char type_of_file)
{
	t_redir_file rf;
	
	rf = malloc(sizeof(struct s_redir_file));
	rf->file_name = file_name;
	rf->file_type = type_of_file;
	return (rf);
}

void		redir_file_destroy(void *rf_)
{
	t_redir_file rf;

	rf = rf_;
	free(rf->file_name);	
	free(rf);
}

t_commands_table	cmd_table(t_pipeline pl, t_dlist env_list)
{
	t_commands_table	ct;

	
	ct = malloc(sizeof(struct s_commands_table));	
	ct->tokens_unproccessed = tokens(pl);
	
	process_tokens_from_quotes(ct->tokens_unproccessed);	
	ct->tokens = empty_arrptr_create(NULL);	
	ct->redir_files = empty_arrptr_create(redir_file_destroy);
	ct->is_after_p_or_sc = pl->is_after_p_or_sc;
	ct->is_there_a_red_error = 0;
	return (ct);
}

void				cmd_table_destroy(void *cmd_tab_)
{
	t_commands_table cmd_tab;

	cmd_tab = (t_commands_table)cmd_tab_;
	/*
	** smth commun between tokens_unpr and tokens
	*/ 
	tokens_destroy(cmd_tab->tokens_unproccessed);
	arrptr_destroy(cmd_tab->tokens);	
	//arrptr_destroy(cmd_tab->redir_files);		
	free(cmd_tab);
}

int	check_if_rd_got_afile(t_commands_table cmdt)
{
	t_tokens up;
	t_syx_check sx;
	

	sx = syntax_check_create();
	up = cmdt->tokens_unproccessed;
	if (up->tokens->cursor_n == up->tokens->sentinel)
		syntax_set_error(sx, "error around redirection sign");	
	
	//|| (up->tokens->cursor_n->value) == '>') || (up->tokens->cursor_n->value) == '<'))

	//	cmdt->is_there_a_red_error = 1;
	return (666);
}		
void	cmd_table_fill(t_commands_table cmdt , t_pipeline pl)
{
	t_tokens up;

	up = cmdt->tokens_unproccessed;
	dlist_move_cursor_to_head(up->tokens);
	dlist_move_cursor_to_head(up->tokens_masks);
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		if (is_normal_token(cmdt))
			arrptr_add(cmdt->tokens, ft_strdup(up->tokens->cursor_n->value));
		else if (is_token_a_r_i_file(cmdt) && check_if_rd_got_afile(cmdt))
			arrptr_add(cmdt->redir_files, redir_file(ft_strdup(up->tokens->cursor_n->value), REDI_INPUT_FILE));
		else if (is_token_a_r_o_file(cmdt) && check_if_rd_got_afile(cmdt))
			arrptr_add(cmdt->redir_files, redir_file(ft_strdup(up->tokens->cursor_n->value), REDI_OUTPUT_FILE));
		else if (is_token_a_r_app_file(cmdt) && check_if_rd_got_afile(cmdt))
			arrptr_add(cmdt->redir_files, redir_file(ft_strdup(up->tokens->cursor_n->value), REDI_APPEND_FILE));
		dlist_move_cursor_to_next(up->tokens);
		dlist_move_cursor_to_next(up->tokens_masks);
	}
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


int					is_normal_token(t_commands_table cmdt)
{
	t_tokens up;		

	up = cmdt->tokens_unproccessed;
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



t_command	*command_table(t_commands_table cmd, t_dlist env_list)
{
	t_command	*command;
	int			i;
		
	command = (t_command *)malloc(sizeof(t_command));
	command->tokens = malloc(sizeof(char*) * (cmd->tokens->len + 1));	
	i = 0;
	while (i < cmd->tokens->len)
	{
		command->tokens[i] = ft_strdup(arrptr_get(cmd->tokens, i));
		i++;
	}
	command->tokens[i] = NULL;
	command->is_after_p_or_sc = cmd->is_after_p_or_sc;
	command->redir_files = cmd->redir_files;
	command->is_there_a_red_error = cmd->is_there_a_red_error;
	//cmd_table_destroy(cmd); // source of the problem
	return (command);
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
	free(cmd_tab->tokens);
	arrptr_destroy(cmd_tab->redir_files);
	free(cmd_tab);
}