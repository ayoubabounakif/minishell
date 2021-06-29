/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __env__.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:38:29 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/06 12:38:30 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	__env__(t_command *command, t_dlist env_list)
{
	t_env		*_420sh_env;

	if (tab_len(command->tokens) != 1)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
	{
		dlist_move_cursor_to_head(env_list);
		while (env_list->cursor_n != env_list->sentinel)
		{
			_420sh_env = env_list->cursor_n->value;
			if (_420sh_env->value == NULL)
				dlist_move_cursor_to_next(env_list);
			else
			{
				printf("%s%c%s\n", _420sh_env->key, _420sh_env->sep, _420sh_env->value);
				dlist_move_cursor_to_next(env_list);
			}
		}
	}
	return (EXIT_SUCCESS);
}
