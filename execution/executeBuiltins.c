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

int executeBuiltins(t_commands_table command, t_dlist envl)
{
	int i;
	const char *builtin_str[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};

	int (*builtin_func[])(t_commands_table  command, t_dlist) = {
		&__echo__,
		&__cd__,
		&__pwd__,
		&__export__,
		&__unset__,
		&__env__,
		&__exit__,
	};

	i = 0;
	while (i < 7)
	{
		if (strcmp(command->tokens_simpl[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(command, envl);
		i++;
	}
	return (EXIT_SUCCESS);
}
