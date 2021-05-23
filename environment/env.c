/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:52:05 by aabounak          #+#    #+#             */
/*   Updated: 2021/04/08 18:52:14 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

t_env	*env_create(char *key, char *value)
{
	t_env *env;

	env = malloc(sizeof(struct s_env));
	env->key = key;
	env->sep = '=';
	env->value = value;
	env->has_value = NO_VALUE;
	return (env);
}


void	env_destroy(void *env_)
{
	t_env *env;

	env = (t_env*)env_;
	free(env->key);
	free(env->value);
	free(env);
}

char	*get_key(char *line)
{
	char	*key;
    char    *tmp;
	int		i = 0;

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
    char    *tmp;
	int		i = 0;

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

t_dlist get_envs(char **env)
{
	int		i = 0;
	t_dlist	list;
	
	list = dlist_empty_create(env_destroy, NULL, NULL);
	while (env[i])
	{
		dlist_pushback(list, env_create(get_key(env[i]), get_value(env[i])));
		i++;
	}
	dlist_move_cursor_to_head(list);
	return (list);
}