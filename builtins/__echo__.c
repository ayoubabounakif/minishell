/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __echo__.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:37:47 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/06 12:37:48 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int __echo__(t_commands_table command, t_dlist env_list)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	while (command->tokens_simpl[i])
	{
		if (i > 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		while (strcmp(command->tokens_simpl[i], "-n") == 0)
		{
			flag = 1;
			i++;
		}
		ft_putstr_fd(command->tokens_simpl[i], STDOUT_FILENO);
		i++;
	}
	if (flag == 0)
		ft_putendl_fd(NULL, STDOUT_FILENO);
	g_vars.exit_code = 0;
	return (EXIT_SUCCESS);
}