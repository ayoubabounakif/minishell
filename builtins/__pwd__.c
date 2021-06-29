/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __pwd__.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:37:54 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/06 12:37:55 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int __pwd__(t_command *command, t_dlist env_list)
{
	(void)env_list;
	char cwd[1024];

	if (command->tokens[1] != NULL)
	{
		ft_putstr_fd("_420sh: pwd doesn't take no options.\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
	{
		chdir(command->tokens[1]);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			return (errno);
		}
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}