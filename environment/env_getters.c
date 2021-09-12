/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:23:01 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/12 17:28:32 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_key(char *line)
{
	char	*key;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	key = ft_strdup("");
	while (line[i] && line[i] != '=')
	{
		tmp = key;
		key = ft_strjoin_c(key, line[i]);
		if (tmp)
			free(tmp);
		i++;
	}
	return (key);
}

char	*get_value(char *line)
{
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	value = ft_strdup("");
	while (line[i] && line[i] != '=')
		i++;
	i++;
	while (line[i])
	{
		tmp = value;
		value = ft_strjoin_c(value, line[i]);
		if (tmp)
			free(tmp);
		i++;
	}
	return (value);
}

char	*ft_getenv(char *name, t_dlist env_list)
{
	t_env	*env;

	dlist_move_cursor_to_head(env_list);
	while (env_list->cursor_n != env_list->sentinel)
	{
		env = env_list->cursor_n->value;
		if (!strcmp(name, env->key))
			return (env->value);
		dlist_move_cursor_to_next(env_list);
	}
	return (NULL);
}

t_dlist	get_envs(char **env)
{
	int				i;
	static t_dlist	list = NULL;

	i = 0;
	if (!list)
	{
		list = dlist_empty_create(env_destroy, NULL, NULL);
		while (env[i])
		{
			dlist_pushback(
				list, env_create(get_key(env[i]), get_value(env[i])));
			i++;
		}
		dlist_move_cursor_to_head(list);
	}
	return (list);
}
