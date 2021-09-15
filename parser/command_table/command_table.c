/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:47:08 by khafni            #+#    #+#             */
/*   Updated: 2021/09/15 14:20:06 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

t_redir_file	redir_file(char *file_name, char type_of_file)
{
	t_redir_file	rf;

	rf = malloc(sizeof(struct s_redir_file));
	rf->file_name = file_name;
	rf->file_type = type_of_file;
	return (rf);
}

void	redir_file_destroy(void *rf_)
{
	t_redir_file	rf;

	rf = rf_;
	free(rf->file_name);
	free(rf);
}

t_commands_table	cmd_table(t_pipeline pl)
{
	t_commands_table	ct;

	ct = malloc(sizeof(struct s_commands_table));
	ct->tokens_unproccessed = tokens(pl);
	ct->tokens = empty_arrptr_create(free);
	ct->redir_files = empty_arrptr_create(redir_file_destroy);
	ct->tokens_simpl = NULL;
	ct->is_after_p_or_sc = pl->is_after_p_or_sc;
	ct->is_there_a_red_error = 0;
	return (ct);
}

void	cmd_table_destroy(void *cmd_tab_)
{
	t_commands_table	cmd_tab;
	int					i;

	i = 0;
	cmd_tab = (t_commands_table)cmd_tab_;
	tokens_destroy(cmd_tab->tokens_unproccessed);
	arrptr_destroy(cmd_tab->tokens);
	arrptr_destroy(cmd_tab->redir_files);
	while (cmd_tab->tokens_simpl[i])
	{
		free(cmd_tab->tokens_simpl[i]);
		i++;
	}
	free(cmd_tab->tokens_simpl[i]);
	free(cmd_tab->tokens_simpl);
	free(cmd_tab);
}

int	check_if_rd_got_afile(t_commands_table cmdt)
{
	t_tokens	up;

	up = cmdt->tokens_unproccessed;
	if (up->tokens->cursor_n == up->tokens->sentinel)
		syntax_set_error("error around redirection sign");
	return (666);
}
