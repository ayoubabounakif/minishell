/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __unset__.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:38:19 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/16 13:40:52 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_env(char **tokens, int i, t_dlist env_list)
{
	t_env	*_420sh_env;

	if (!(env_list))
		return ;
	dlist_move_cursor_to_head((env_list));
	while ((env_list)->cursor_n != (env_list)->sentinel)
	{
		_420sh_env = (env_list)->cursor_n->value;
		if (strcmp(_420sh_env->key, tokens[i]) == 0)
			dlist_remove_after_cursor((env_list), 1);
		dlist_move_cursor_to_next((env_list));
	}
}

static int	checkSyntax(char *token)
{
	int		i;

	i = 0;
	while (token[i] == ' ')
		i++;
	if (ft_isdigit(token[i]) == TRUE)
		return (FALSE);
	if (ft_isalpha(token[i]) == FALSE)
		return (FALSE);
	i++;
	while (token[i])
	{
		if (ft_isalnum(token[i]) == FALSE)
			return (FALSE);
		else
			i++;
	}
	return (TRUE);
}

int	__unset__(t_commands_table command, t_dlist env_list)
{
	int	i;
	int	flag;

	flag = 1;
	if (tab_len(command->tokens_simpl) > 1)
	{
		i = 0;
		while (command->tokens_simpl[++i])
		{
			if (checkSyntax(command->tokens_simpl[i]) == TRUE)
				unset_env(command->tokens_simpl, i, env_list);
			else
			{
				g_vars.exit_code = 1;
				printf("420sh: unset: `%s': not a valid identifier\n",
					command->tokens_simpl[i]);
				return (g_vars.exit_code);
			}
		}
	}
	return (EXIT_SUCCESS);
}
