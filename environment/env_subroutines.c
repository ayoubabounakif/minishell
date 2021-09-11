/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_subroutines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:25:48 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/11 13:26:09 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*env_create(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(struct s_env));
	env->key = key;
	env->sep = '=';
	if (value)
		env->value = value;
	else
		env->value = NULL;
	return (env);
}

void	env_destroy(void *env_)
{
	t_env	*env;

	env = (t_env *)env_;
	free(env->key);
	free(env->value);
	free(env);
}

void	env_array_destroy(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array[i]);
	free(env_array);
}
