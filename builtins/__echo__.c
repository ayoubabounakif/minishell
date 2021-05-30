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

int __echo__(t_command *command, t_dlist env_list)
{
	(void)env_list;
	int i;
	int flag;

	i = 1;
	flag = 0;
	while (command->tokens[i])
	{
		if (i > 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		while (strcmp(command->tokens[i], "-n") == 0)
		{
			flag = 1;
			i++;
		}
		ft_putstr_fd(command->tokens[i], STDOUT_FILENO);
		i++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (command->is_pipe == 1)
		exit(0);
	return (0);
}