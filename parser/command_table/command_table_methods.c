/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_methods.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:40:33 by khafni            #+#    #+#             */
/*   Updated: 2021/09/11 14:35:21 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	cmd_table_fill_helper(t_commands_table cmdt)
{
	t_tokens	up;
	char		*tmp_str;
	void		**v;
	t_arrptr	ar;

	*v = NULL;
	(void)(tmp_str);
	up = cmdt->tokens_unproccessed;
	dlist_move_cursor_to_head(up->tokens);
	dlist_move_cursor_to_head(up->tokens_masks);
	while (up->tokens->cursor_n != up->tokens->sentinel)
	{
		*v = up->tokens->cursor_n->value;
		ar = cmdt->redir_files;
		if (is_normal_token(cmdt))
			arrptr_add(cmdt->tokens, ft_strdup(*v));
		else if (is_token_a_r_i_file(cmdt) && check_if_rd_got_afile(cmdt))
			arrptr_add(ar, redir_file(ft_strdup(*v), REDI_INPUT_FILE));
		else if (is_token_a_r_o_file(cmdt) && check_if_rd_got_afile(cmdt))
			arrptr_add(ar, redir_file(ft_strdup(*v), REDI_OUTPUT_FILE));
		else if (is_token_a_r_app_file(cmdt) && check_if_rd_got_afile(cmdt))
			arrptr_add(ar, redir_file(ft_strdup(*v), REDI_APPEND_FILE));
		else if (is_token_a_r_heredoc_file(cmdt) && check_if_rd_got_afile(cmdt))
			arrptr_add(ar, redir_file(ft_strdup(*v), REDI_HEREDOC_FILE));
		dlist_move_cursor_to_next(up->tokens);
		dlist_move_cursor_to_next(up->tokens_masks);
	}
}



void	cmd_table_fill(t_commands_table cmdt)
{
	int	i;

	cmd_table_fill_helper(cmdt);
	cmdt->tokens_simpl = malloc(sizeof(char *) * (cmdt->tokens->len + 1));
	i = 0;
	while (i < cmdt->tokens->len)
	{	
		cmdt->tokens_simpl[i] = ft_strdup(arrptr_get(cmdt->tokens, i));
		i++;
	}
	cmdt->tokens_simpl[cmdt->tokens->len] = NULL;
}

void	cmd_table_fill_tokens(t_commands_table cmdt)
{
	t_tokens	up;

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

t_command	*command_table(t_commands_table cmd)
{
	t_command	*command;
	int			i;

	command = (t_command *)malloc(sizeof(t_command));
	command->tokens = malloc(sizeof(char *) * (cmd->tokens->len + 1));
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
	return (command);
}

void	command_table_destroy(void *cmd_tab_)
{
	int			i;
	t_command	*cmd_tab;

	cmd_tab = (t_command *)cmd_tab_;
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
