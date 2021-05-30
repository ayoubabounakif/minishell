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
		ft_putstr_fd("aksh: pwd doesn't take no options.\n", STDERR_FILENO);
	else
	{
		chdir(command->tokens[1]);
		getcwd(cwd, sizeof(cwd));
		printf("Current working directory: %s\n", cwd);
	}
	return (1);
}