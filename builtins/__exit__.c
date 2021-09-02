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

	if (*ac > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_vars.exit_code = 1;
		return (errno);
	}
	if (tokens[1])
	{
		j = 0;
		while (tokens[1][j])
		{
			if (!ft_isdigit(tokens[1][j]))
			{
			/* 	ft_putstr_fd("exit\n", STDERR_FILENO);
				printErrorMessage("exit", ": ");
				ft_putstr_fd(tokens[1], STDERR_FILENO);
				ft_putstr_fd(": numeric argument required\n", STDERR_FILENO); */
				printErrorMessage("exit", "numeric argument required");
				// ft_putendl_fd(strerror(errno), STDERR_FILENO);
				return (errno);
			}
			j++;
		}
	}
	return (EXIT_SUCCESS);
}

/*
**	exit needs to work better with exit statuses, and the while and if dont work the right way
*/
int __exit__(t_commands_table command, t_dlist env_list)
{
	int		i;
	(void)env_list;

	i = 0;
	while (command->tokens_simpl[i] != NULL)
		i++;
	if (i == 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(9999);
	}
	else
	{
		if (exitSyntaxChecker(&i, command->tokens_simpl) == EXIT_FAILURE)
		{
			g_vars.exit_code = 255;
			exit(9999);
		}
		else
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			g_vars.exit_code = 9999;
			exit(9999);
		}
	}
	return (EXIT_SUCCESS);
}
