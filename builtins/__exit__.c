/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit__.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:38:02 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/16 14:00:11 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exitSyntaxChecker(char **tokens)
{
	int		j;

	if (tokens[1])
	{
		j = 0;
		while (tokens[1][j])
		{
			if (!ft_isdigit(tokens[1][j]))
				return (EXIT_FAILURE);
			j++;
		}
	}
	return (EXIT_SUCCESS);
}

void	executeExitFunct(t_commands_table command)
{
	if (exitSyntaxChecker(command->tokens_simpl) != EXIT_SUCCESS)
	{
		printErrorMessage("exit", "numeric argument required ");
		g_vars.exit_code = 255;
		exit(g_vars.exit_code);
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		g_vars.exit_code = ft_atoi(command->tokens_simpl[1]);
		exit(g_vars.exit_code);
	}
}

int	__exit__(t_commands_table command, t_dlist env_list)
{
	int	i;

	(void)env_list;
	i = 0;
	if (tab_len(command->tokens_simpl) > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		printErrorMessage(command->tokens_simpl[0], "too many arguments ");
		g_vars.exit_code = 1;
		return (g_vars.exit_code);
	}
	if (!command->tokens_simpl[1])
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		g_vars.exit_code = g_vars.exit_code;
		exit(g_vars.exit_code);
	}
	else
		executeExitFunct(command);
	return (EXIT_SUCCESS);
}
