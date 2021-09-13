/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:20:24 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/13 18:39:38 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expandNormalTokens(void *data, t_dlist env_lst)
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
		if (cstr_lookup(mask, "$V"))
		{
			tmp_str = ft_itoa(g_vars.exit_code);
			cmd->tokens_simpl[i]
				= find_replace_env_vars_in_a_token(
					cmd->tokens_simpl[i], env_lst);
			cmd->tokens_simpl[i]
				= str_find_and_replace(
					cmd->tokens_simpl[i], "$?", tmp_str);
			free(tmp_str);
		}
		free(mask);
		i++;
	}
}

void	expandRedirFiles(void *data, t_dlist env_lst)
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
		if (ft_strnstr(file_name, "$?", ft_strlen(file_name)))
		{
			tmp_str = ft_itoa(g_vars.exit_code);
			((t_redir_file)arrptr_get(cmd->redir_files, i))->file_name
			= str_find_and_replace(file_name, "$?", tmp_str);
		}
		else if (ft_strnstr(file_name, "$", ft_strlen(file_name)))
			file_name
				= find_replace_env_vars_in_a_token(file_name, env_lst);
		i++;
	}
}

void	last_commandCode_expend(t_dlist env_lst)
{
	char	*lastCmdCode;
	t_env	*env;
	t_env	*env_tmp;

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
}

void	expandEnvVarsInParsedData(t_dlist parsed_data_lst, t_dlist env_lst)
{
	dlist_move_cursor_to_head(parsed_data_lst);
	while (parsed_data_lst->cursor_n != parsed_data_lst->sentinel)
	{
		expandNormalTokens(parsed_data_lst->cursor_n->value, env_lst);
		expandRedirFiles(parsed_data_lst->cursor_n->value, env_lst);
		dlist_move_cursor_to_next(parsed_data_lst);
	}
}
