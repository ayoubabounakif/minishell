/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:20:24 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/15 19:35:20 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expandNormalTokens_helper(t_ent *ent)
{
	t_commands_table	cmd;

	cmd = ent->cmd;
	ent->mask = get_mask(cmd->tokens_simpl[ent->i]);
	if (cstr_lookup(ent->mask, "$V"))
	{		
		ent->tmp_str = ft_itoa(g_vars.exit_code);
		cmd->tokens_simpl[ent->i]
			= find_replace_env_vars_in_a_token(
				cmd->tokens_simpl[ent->i], ent->env_lst);
		cmd->tokens_simpl[ent->i]
			= str_find_and_replace(
				cmd->tokens_simpl[ent->i], "$?", ent->tmp_str);
		free(ent->tmp_str);
	}
	if (cstr_lookup(ent->mask, "$V"))
	{
		destroy_mask(&ent->mask);
		free(ent->mask);
		expandNormalTokens(ent->cmd, ent->env_lst);
	}
}

void	expandNormalTokens(void *data, t_dlist env_lst)
{
	t_ent				ent;
	t_commands_table	cmd;

	ent.env_lst = env_lst;
	ent.cmd = data;
	ent.mask = NULL;
	ent.i = 0;
	cmd = ent.cmd;
	while (ent.i < cmd->tokens->len)
	{
		expandNormalTokens_helper(&ent);
		destroy_mask(&ent.mask);
		destroy_mask(&ent.mask);
		ent.i++;
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
		if (cstr_lookup(file_name, "$?"))
		{
			tmp_str = ft_itoa(g_vars.exit_code);
			((t_redir_file)arrptr_get(cmd->redir_files, i))->file_name
			= str_find_and_replace(file_name, "$?", tmp_str);
		}
		else if (cstr_lookup(file_name, "$"))
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
