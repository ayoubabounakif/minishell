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

static const char *builtin_str[] = {
	"echo",
	"cd",
	"pwd",
	"export",
	"unset",
	"env",
	"exit",
};

static int (*builtin_func[])(t_command *command, t_dlist) = {
	&__echo__,
	&__cd__,
	&__pwd__,
	&__export__,
	&__unset__,
	&__env__,
	&__exit__,
};

int	spawnLastProc(int in, int *pipeFds, t_command *command, t_dlist envl)
{
	int		i;

	expand_env_variables_test(command, envl);
	if (isBuiltin(command->tokens[0], builtin_str) == FALSE)
	{
		command->tokens[0] = binPath(command->tokens[0], envl);
		if (command->tokens[0] == NULL)
			return (EXIT_FAILURE);
	}
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
		i = 0;
		if (isBuiltin(command->tokens[0], builtin_str) == TRUE)
		{
			i = 0;
			while (i < 7)
			{
				if (strcmp(command->tokens[0], builtin_str[i]) == 0)
					return (*builtin_func[i])(command, envl);
				i++;
			}
		}
		else
			execve(command->tokens[0], command->tokens, env_list_to_env_array(envl));
	}
	return (EXIT_SUCCESS);
}

int	spawnProc(int in, int *pipeFds, t_command *command, t_dlist envl)
{
	int		i;

	expand_env_variables_test(command, envl);
	if (isBuiltin(command->tokens[0], builtin_str) == FALSE)
	{
		command->tokens[0] = binPath(command->tokens[0], envl);
		if (command->tokens[0] == NULL)
			return (EXIT_FAILURE);
	}
	g_vars.pid = fork();
	if (g_vars.pid == CHILD_PROCESS)
	{
		dup2InputOutput(in, pipeFds[WRITE]);
		if (pipeFds[READ] > 2)
			close(pipeFds[READ]);
		if (command->redir_files->len != 0)
			inputOutputRedirection(command);
		if (isBuiltin(command->tokens[0], builtin_str) == TRUE)
		{
			i = 0;
			while (i < 7)
			{
				if (strcmp(command->tokens[0], builtin_str[i]) == 0)
					return (*builtin_func[i])(command, envl);
				i++;
			}
		}
		else
			execve(command->tokens[0], command->tokens, env_list_to_env_array(envl));
	}
	return (EXIT_SUCCESS);
}
