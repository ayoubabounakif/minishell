/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeBuiltins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:08:59 by aabounak          #+#    #+#             */
/*   Updated: 2021/07/06 18:09:19 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	executeBuiltin(
	t_commands_table command,
	const char *builtin_str[],
	int (*builtin_func[])(t_commands_table command, t_dlist),
	t_dlist	envl)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (strcmp(command->tokens_simpl[0], builtin_str[i]) == 0)
			return ((*builtin_func[i])(command, envl));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	executeBuiltins(t_commands_table command, t_dlist envl)
{
	const char		*builtin_str[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};
	static	int		(*builtin_func[])(t_commands_table command, t_dlist) = {
		&__echo__,
		&__cd__,
		&__pwd__,
		&__export__,
		&__unset__,
		&__env__,
		&__exit__,
	};

	return (executeBuiltin(command, builtin_str, builtin_func, envl));
}
