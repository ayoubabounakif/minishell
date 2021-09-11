/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_methods1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 15:29:42 by khafni            #+#    #+#             */
/*   Updated: 2021/09/11 15:30:44 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

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
