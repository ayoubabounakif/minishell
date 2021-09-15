/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:52:05 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/15 19:28:25 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_3_strings(char *s1, char *s2, char *s3)
{
	char	*r_str;
	char	*r_str_tmp;

	r_str = ft_strjoin(s1, s2);
	r_str_tmp = r_str;
	r_str = ft_strjoin(r_str, s3);
	free(r_str_tmp);
	return (r_str);
}

char	**env_list_to_env_array(t_dlist env_list)
{
	t_env	*e;
	char	**env_array;
	char	*joined_str;
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

char	*find_envv_akey_value(char *key, t_dlist env_list)
{
	int		is_it_found;
	t_env	*env;

	is_it_found = 0;
	if (*key == '$')
		key += 1;
	dlist_move_cursor_to_head(env_list);
	while (env_list->cursor_n != env_list->sentinel)
	{
		env = env_list->cursor_n->value;
		if (is_cstrs_equal(key, env->key))
			return (env->value);
		dlist_move_cursor_to_next(env_list);
	}
	return (NULL);
}

t_env	*find_envv_key_node(char *key, t_dlist env_list)
{
	int		is_it_found;
	t_env	*env;

	is_it_found = 0;
	if (*key == '$')
		key += 1;
	dlist_move_cursor_to_head(env_list);
	while (env_list->cursor_n != env_list->sentinel)
	{
		env = env_list->cursor_n->value;
		if (!ft_strncmp(key, env->key, ft_strlen(key)))
			return (env);
		dlist_move_cursor_to_next(env_list);
	}
	return (NULL);
}
