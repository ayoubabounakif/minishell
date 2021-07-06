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

int	executeBuiltins(t_command *command, t_dlist envl)
{
	int		i;
	const char *builtin_str[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};

	int (*builtin_func[])(t_command *command, t_dlist) = {
		&__echo__,
		&__cd__,
		&__pwd__,
		&__export__,
		&__unset__,
		&__env__,
		&__exit__,
	};

	i = 0;
	while (i < 7)
	{
		if (strcmp(command->tokens[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(command, envl);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	spawnLastProc(int in, int *pipeFds, t_command *command, t_dlist envl)
{
	if (isBuiltin(command->tokens[0]) == TRUE)
		return (executeBuiltins(command, envl));
	g_vars.pid = fork();
	if (g_vars.pid == CHILD_PROCESS)
	{
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (pipeFds[WRITE] > 2)
			close(pipeFds[WRITE]);
		if (command->redir_files->len != 0)
			inputOutputRedirection(command);
		if (isBuiltin(command->tokens[0]) == TRUE)
			exit(executeBuiltins(command, envl));
		else
			execve(command->tokens[0], command->tokens, env_list_to_env_array(envl));
	}
	return (EXIT_SUCCESS);
}

int	spawnProc(int in, int *pipeFds, t_command *command, t_dlist envl)
{
	g_vars.pid = fork();
	if (g_vars.pid == CHILD_PROCESS)
	{
		dup2InputOutput(in, pipeFds[WRITE]);
		if (pipeFds[READ] > 2)
			close(pipeFds[READ]);
		if (command->redir_files->len)
			inputOutputRedirection(command);
		if (isBuiltin(command->tokens[0]) == TRUE)
			exit(executeBuiltins(command, envl));
		else
			execve(command->tokens[0], command->tokens, env_list_to_env_array(envl));
	}
	return (EXIT_SUCCESS);
}