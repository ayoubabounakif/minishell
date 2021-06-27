/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:52:05 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/30 16:20:36 by khafni           ###   ########.fr       */
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

char		*join_3_strings(char *s1, char *s2, char *s3)
{
	char *r_str;
	char *r_str_tmp;

	r_str = ft_strjoin(s1, s2);
	r_str_tmp = r_str;
	r_str = ft_strjoin(r_str, s3);
	free(r_str_tmp);
	return (r_str);
}

char		**env_list_to_env_array(t_dlist env_list)
{
	t_env *e;
	char	**env_array;
	char *joined_str;
	char *joined_str_tmp;
	int i;

	env_array = malloc((sizeof(char*) * env_list->len) + 1);
	i = 0;
	dlist_move_cursor_to_head(env_list);	
	while (env_list->cursor_n != env_list->sentinel)
	{
		e = env_list->cursor_n->value;	
		joined_str = join_3_strings(e->key, "=", e->value);
		env_array[i] = joined_str;
		dlist_move_cursor_to_next(env_list);
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	env_array_destroy(char **env_array)
{
	int i;

	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array[i]);
	free(env_array);
}

char	*find_envv_akey_value(char *key, t_dlist env_list)
{
	int is_it_found;
	t_env	*env;

	is_it_found = 0;
	if (*key == '$')
		key+=1;
	dlist_move_cursor_to_head(env_list);
	while(env_list->cursor_n != env_list->sentinel)
	{
		env = env_list->cursor_n->value;
		if (!ft_strncmp(key, env->key, ft_strlen(key)))		
			return (env->value);
		dlist_move_cursor_to_next(env_list);
	}
	return (NULL);
}