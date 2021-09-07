/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:52:05 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/07 14:00:44 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

t_env	*env_create(char *key, char *value)
{
	t_env *env;

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
	t_env *env;

	env = (t_env *)env_;
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

/*
** implementation of getenv
*/
char    *ft_getenv(char *name, t_dlist env_list)
{
    t_env	*env;

    dlist_move_cursor_to_head(env_list);
	while(env_list->cursor_n != env_list->sentinel)
	{
		env = env_list->cursor_n->value;
		if (!ft_strncmp(name, env->key, ft_strlen(name)))		
			return (env->value);
		dlist_move_cursor_to_next(env_list);
	}
	return (NULL);
}

t_dlist get_envs(char **env)
{
	int		i = 0;
	static t_dlist	list = NULL;
	
	if (!list)
	{
		list = dlist_empty_create(env_destroy, NULL, NULL);
		while (env[i])
		{
			dlist_pushback(list, env_create(get_key(env[i]), get_value(env[i])));
			i++;
		}
		dlist_move_cursor_to_head(list);
	}
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
	t_env	*e;
	char	**env_array;
	char	*joined_str;
	char	*joined_str_tmp;
	int		i;

	env_array = (char **)malloc((sizeof(char *) * (env_list->len + 1)));
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

t_env *find_envv_key_node(char *key, t_dlist env_list)
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
			return (env);
		dlist_move_cursor_to_next(env_list);
	}
	return (NULL);
}

void        last_commandCode_expend(t_dlist env_lst)
{
	char *lastCmdCode;
	t_env *env;
	// char *value;
	t_env *env_tmp;
	// exit(666);
	// value = find_envv_akey_value("?", env_lst);
	
	env_tmp = find_envv_key_node("?", env_lst);
	if (env_tmp != NULL)
	{
		free(env_tmp->value);
		env_tmp->value = ft_itoa(g_vars.exit_code);
		return ;
	}
	lastCmdCode = ft_itoa(g_vars.exit_code);
	env = env_create(ft_strdup("?"), ft_strdup(lastCmdCode));
	env->sep = '=';
	dlist_move_cursor_to_tail(env_lst);
	dlist_insert_before_cursor(env_lst, env);
	dlist_move_cursor_to_head(env_lst);
	// while (env_lst->cursor_n != env_lst->sentinel)
	// {
	// 	printf("|%s %s|\n", ((t_env *)env_lst->cursor_n->value)->key, ((t_env *)env_lst->cursor_n->value)->value);
	// 	dlist_move_cursor_to_next(env_lst);
	// }
}

void		expandNormalTokens(void *data, t_dlist env_lst)
{
	t_commands_table	cmd;
	int					i;
	char				*tmp_str;
	char				*mask;
	
	mask = NULL;
	i = 0;
	cmd = data;
	while (i < cmd->tokens->len)
	{
		mask = get_mask(cmd->tokens_simpl[i]);
		/* if (ft_strnstr(cmd->tokens_simpl[i] , "$?", ft_strlen(cmd->tokens_simpl[i]))
		&& ft_strnstr(mask, "$V", ft_strlen(mask)))
			{
				tmp_str = ft_itoa(g_vars.exit_code);
				cmd->tokens_simpl[i] = str_find_and_replace(cmd->tokens_simpl[i], "$?", tmp_str);
			}	 */
		if (ft_strnstr(mask, "$V", ft_strlen(mask)))
			{
				tmp_str = ft_itoa(g_vars.exit_code);
				// cmd->tokens_simpl[i] = str_find_and_replace(cmd->tokens_simpl[i], "$?", tmp_str);
				cmd->tokens_simpl[i] = find_replace_env_vars_in_a_token(cmd->tokens_simpl[i], env_lst);
				cmd->tokens_simpl[i] = str_find_and_replace(cmd->tokens_simpl[i], "$?", tmp_str);
				free(tmp_str);
			}
		free(mask);
		i++;
	}	
}

void		expandRedirFiles(void *data, t_dlist env_lst)
{
	t_commands_table	cmd;
	int					i;
	char				*tmp_str;
	char				*file_name;

	i = 0;
	cmd = data;
	while (i < cmd->redir_files->len)
	{
		file_name = ((t_redir_file)arrptr_get(cmd->redir_files, i))->file_name;
		if (ft_strnstr(file_name , "$?", ft_strlen(file_name)))
			{
				tmp_str = ft_itoa(g_vars.exit_code);
				((t_redir_file)arrptr_get(cmd->redir_files, i))->file_name = str_find_and_replace(file_name, "$?", tmp_str);
			}	
			else if (ft_strnstr(file_name, "$", ft_strlen(file_name)))
				file_name = find_replace_env_vars_in_a_token(file_name, env_lst);
		i++;
	}
}

void		expandEnvVarsInParsedData(t_dlist parsed_data_lst, t_dlist env_lst)
{
	dlist_move_cursor_to_head(parsed_data_lst);
	while (parsed_data_lst->cursor_n != parsed_data_lst->sentinel)
	{
		expandNormalTokens(parsed_data_lst->cursor_n->value, env_lst);	
		expandRedirFiles(parsed_data_lst->cursor_n->value, env_lst);		
		dlist_move_cursor_to_next(parsed_data_lst);
	}
}