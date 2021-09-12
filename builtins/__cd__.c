/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __cd__.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:37:37 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/06 12:37:38 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	__cd__(t_commands_table command, t_dlist env_list)
{
	char	*cmd;
	char	*arg;

	cmd = command->tokens_simpl[0];
	arg = command->tokens_simpl[1];
	if (arg == NULL)
	{
		arg = ft_getenv("HOME", env_list);
		if (!arg)
		{
			printErrorMessage(cmd, "HOME not set");
			g_vars.exit_code = 1;
			return (errno);
		}
	}
	if (chdir(arg) == 0)
		return (EXIT_SUCCESS);
	else
	{
		printErrorMessage(cmd, arg);
		g_vars.exit_code = 1;
		return (errno);
	}
	g_vars.exit_code = 0;
	return (EXIT_SUCCESS);
}
