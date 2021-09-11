/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawnProc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:22:51 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/27 17:23:02 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	spawnLastProc(int in, int *pipeFds, t_commands_table command, t_dlist envl)
{
	if (isBuiltin(command->tokens_simpl[0]) == TRUE
		&& !command->redir_files->len)
		return (executeBuiltins(command, envl));
	g_vars.pid = fork();
	if (g_vars.pid == CHILD)
	{
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (pipeFds[WRITE] > 2)
			close(pipeFds[WRITE]);
		if (command->redir_files->len)
			inputOutputRedirection(command);
		if (isBuiltin(command->tokens_simpl[0]) == TRUE)
			exit(executeBuiltins(command, envl));
		else
		{
			if (command->tokens_simpl[0] == NULL)
				exit(g_vars.exit_code);
			execve(
				command->tokens_simpl[0],
				command->tokens_simpl,
				env_list_to_env_array(envl));
		}
	}
	return (EXIT_SUCCESS);
}

int	spawnProc(int in, int *pipeFds, t_commands_table command, t_dlist envl)
{
	g_vars.pid = fork();
	if (g_vars.pid == CHILD)
	{
		dup2InputOutput(in, pipeFds[WRITE]);
		if (pipeFds[READ] > 2)
			close(pipeFds[READ]);
		if (command->redir_files->len)
			inputOutputRedirection(command);
		if (isBuiltin(command->tokens_simpl[0]) == TRUE)
			exit(executeBuiltins(command, envl));
		else
		{
			if (command->tokens_simpl[0] == NULL)
				exit(g_vars.exit_code);
			execve(
				command->tokens_simpl[0],
				command->tokens_simpl,
				env_list_to_env_array(envl));
		}
	}
	return (EXIT_SUCCESS);
}
