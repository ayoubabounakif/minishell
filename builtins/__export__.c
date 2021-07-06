/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __export__.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:39:02 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/30 16:45:37 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** The Open Group Base Specifications Issue 6
** IEEE Std 1003.1, 2004 Edition
** /https://pubs.opengroup.org/onlinepubs/009695299/basedefs/xbd_chap08.html
*/

static int	__export_env__(char **tokens, t_dlist env_list)
{
	(void)tokens;
	t_env		*_420sh_env;

	dlist_move_cursor_to_head(env_list);
	while (env_list->cursor_n != env_list->sentinel)
	{
		_420sh_env = env_list->cursor_n->value;
		if (_420sh_env->value == NULL)
			printf("declare -x %s\n", _420sh_env->key);
		else
			printf("declare -x %s%c\"%s\"\n", _420sh_env->key, _420sh_env->sep, _420sh_env->value);
		dlist_move_cursor_to_next(env_list);
	}
	return (1);
}

static int	check_syntax(char *token)
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
	while (token[i] && token[i] != '=')
	{
		if (ft_isalnum(token[i]) == FALSE)
			return (FALSE);
		else
			i++;
	}
	return (TRUE);
}

# define NO_CHANGE 10

/*
** The paramater string, will contain key if eq_sign == 1
** It will contain the full token if eq_sign == 0 (The token won't have a value so it'll only be the key)
*/
static int		check_env(char *string, t_dlist env_list, int eq_sign)
{
	t_env 	*_420sh_env;

	dlist_move_cursor_to_head(env_list);
	while (env_list->cursor_n != env_list->sentinel)
	{
		_420sh_env = env_list->cursor_n->value;
		if (eq_sign == TRUE) // There is eq sign
		{
			if (strcmp(_420sh_env->key, string) == 0)
				dlist_remove_after_cursor(env_list, 1);
			dlist_move_cursor_to_next(env_list);
		}
		else if (eq_sign == FALSE) // There is no eq sign
		{
			if (strcmp(_420sh_env->key, string) == 0 && _420sh_env->value == NULL)
				dlist_remove_after_cursor(env_list, 1);
			else if (strcmp(_420sh_env->key, string) == 0 && _420sh_env->value != NULL)
				return (NO_CHANGE);
			dlist_move_cursor_to_next(env_list);
		}
	}
	return (TRUE);
}

static int	exportHelper(char *token, t_dlist env_list)
{
	char	**key_value;
	env_list = get_envs(NULL);

	if (check_syntax(token) == TRUE)
	{
		if (strchr(token, '='))
		{
			key_value = ft_split_first_sep(token, '=');
			if (check_env(key_value[0], env_list, 1) == 1)
				dlist_pushback(env_list, env_create(key_value[0], key_value[1]));
		}
		else if (!(strchr(token, '=')))
		{
			if (check_env(token, env_list, 0) == 1)
				dlist_pushback(env_list, env_create(token, NULL));
		}
	}
	else
		printf("420sh: export: `%s': not a valid identifier\n", token);
	
	return (EXIT_SUCCESS);
}

int	__export__(t_command *command, t_dlist env_list)
{
	int		i;

	if (tab_len(command->tokens) > 1)
	{
		i = 1;
		while (command->tokens[i])
		{
			exportHelper(command->tokens[i], env_list);
			i++;
		}
	}
	else if (tab_len(command->tokens) == 1)
		__export_env__(command->tokens, env_list);
	return (EXIT_SUCCESS);
}
