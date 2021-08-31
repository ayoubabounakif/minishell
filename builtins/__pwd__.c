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

int __pwd__(t_commands_table command, t_dlist env_list)
{
	(void)env_list;
	char cwd[1024];

	chdir(command->tokens_simpl[1]);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}