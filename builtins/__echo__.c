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

#define OUTPUT_TRAILING_NEWLINE 1
#define SUPPRESS_OUTPUT_TRAILING_NEWLINE 0

void	setFlagNIndex(char **tokens, int *flagRef, int *indexRef)
{
	if (strcmp(tokens[1], "-n") == 0)
		(*flagRef) = SUPPRESS_OUTPUT_TRAILING_NEWLINE;
	if (*flagRef == SUPPRESS_OUTPUT_TRAILING_NEWLINE)
		(*indexRef) = 2;
}

int	checkToken(char **tokens)
{
	if (!tokens[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_vars.exit_code = 0;
		return (0);
	}
	return (1);
}

int	__echo__(t_commands_table command, t_dlist env_list)
{
	int		i;
	int		flag;
	char	**tokens;

	tokens = command->tokens_simpl;
	if (!checkToken(tokens))
		return (EXIT_SUCCESS);
	(i) = 1;
	(flag) = OUTPUT_TRAILING_NEWLINE;
	setFlagNIndex(tokens, (&flag), (&i));
	while (tokens[i])
	{
		ft_putstr_fd(tokens[i], STDOUT_FILENO);
		if (tokens[(i) + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		(i)++;
	}
	if ((flag) == OUTPUT_TRAILING_NEWLINE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_vars.exit_code = 0;
	return (EXIT_SUCCESS);
}
