/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit__.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:38:02 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/06 12:38:03 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exitSyntaxChecker(int *ac, char **tokens)
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

int __exit__(t_commands_table command, t_dlist env_list)
{
	int		i;

	i = 0;
	if (!command->tokens_simpl[1])
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		g_vars.exit_code = g_vars.exit_code;
		exit(g_vars.exit_code);
	}
	else
	{
		if (exitSyntaxChecker(&i, command->tokens_simpl) != EXIT_SUCCESS)
		{
			printErrorMessage("exit", "");
			g_vars.exit_code = 255;
			exit(g_vars.exit_code);
		}
		else
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			g_vars.exit_code = ft_atoi(command->tokens_simpl[1]);
			exit(g_vars.exit_code);
		}
	}
	return (EXIT_SUCCESS);
}
