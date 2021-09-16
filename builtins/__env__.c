/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __env__.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:38:02 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/16 14:01:19 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define ALL_GOOD 1
#define ERROR 0

static int	checkArgs(char **tokens)
{
	if (tab_len(tokens) != 1)
	{
		printErrorMessage(tokens[1], "No such file or directory");
		g_vars.exit_code = 127;
		return (ERROR);
	}
	return (ALL_GOOD);
}

int	__env__(t_commands_table command, t_dlist env_list)
{
	t_env		*_420sh_env;

	if (!checkArgs(command->tokens_simpl))
		return (EXIT_FAILURE);
	else
	{
		dlist_move_cursor_to_head(env_list);
		while ((env_list)->cursor_n != (env_list)->sentinel)
		{
			_420sh_env = (env_list)->cursor_n->value;
			if (_420sh_env->value == NULL)
				dlist_move_cursor_to_next(env_list);
			else
			{
				printf("%s%c%s\n",
					_420sh_env->key, _420sh_env->sep, _420sh_env->value);
				dlist_move_cursor_to_next(env_list);
			}
		}
	}
	g_vars.exit_code = 0;
	return (EXIT_SUCCESS);
}
