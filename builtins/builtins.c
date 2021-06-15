/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:49:10 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/15 15:55:27 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *builtin_str[] = {
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

int num_builtins(void)
{
	return (sizeof(builtin_str) / sizeof(char *));
}

char *bin_path(char *cmd, t_dlist envl)
{
	t_env *_420sh_env;
	int bin_fd;
	char *path;
	char *bin_path;
	char **split_path;
	int i;

	i = 0;
	bin_path = NULL;
	dlist_move_cursor_to_head(envl);
	while (envl->cursor_n != envl->sentinel)
	{
		_420sh_env = envl->cursor_n->value;
		if (strcmp(_420sh_env->key, "PATH") == 0)
			path = _420sh_env->value;
		dlist_move_cursor_to_next(envl);
	}
	split_path = ft_split(path, ':');
	if (split_path == NULL)
	{
		ft_putstr_fd("_420sh: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (NULL);
	}
	while (split_path[i])
	{
		bin_path = ft_strjoin(split_path[i], "/");
		bin_path = ft_strjoin(bin_path, cmd);
		bin_fd = open(bin_path, O_RDONLY);
		if (bin_fd > 0)
		{
			close(bin_fd);
			return (bin_path);
		}
		i++;
	}
	ft_putstr_fd("_420sh: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	i = 0;
	free(bin_path);
	while (split_path[i])
	{
		free(split_path[i]);
		i++;
	}
	free(split_path);
	return (NULL);
}

int		spawn_proc_lcmd(int in, t_command *command, t_dlist envl)
{
	int		j;
	char	*bin;

	j = 0;
	expand_env_variables_test(command, envl);
	// g_vars.pid = fork();
	// if (g_vars.pid == CHILD_PROCESS) // Meaning we're in the child process
	// {
	// 	while (j < num_builtins())
	// 	{
	// 		if (strcmp(command->tokens[0], builtin_str[j]) == 0)
	// 			return (*builtin_func[j])(command, envl);
	// 		j++;
	// 	}
	// 	if (in != STDIN_FILENO)
	// 	{
	// 		dup2(in, STDIN_FILENO);
	// 		close(in);
	// 	}
	// 	bin = bin_path(command->tokens[0], envl);
	// 	if (bin == NULL)
	// 		return (EXIT_FAILURE);
	// 	// envp should change by khalils method
	// 	execve(bin, command->tokens, env_list_to_env_array(envl));
	// }
	// IN CASE we have a pipe we should fork for the builtins too
	if (command->is_pipe == TRUE)
	{
		g_vars.pid = fork();
		if (g_vars.pid == CHILD_PROCESS) // Meaning we're in the child process
		{
			while (j < num_builtins())
			{
				if (strcmp(command->tokens[0], builtin_str[j]) == 0)
					return (*builtin_func[j])(command, envl);
				j++;
			}
			// if (in != STDIN_FILENO)
			// {
			// 	dup2(in, STDIN_FILENO);
			// 	close(in);
			// }
			bin = bin_path(command->tokens[0], envl);
			if (bin == NULL)
				return (EXIT_FAILURE);
			execve(bin, command->tokens, env_list_to_env_array(envl));
		}
	}
	// IN CASE OF NO pipe, we don't need to fork for the builtins
	else if (command->is_pipe != TRUE)
	{
		while (j < num_builtins())
		{
			if (strcmp(command->tokens[0], builtin_str[j]) == 0)
				return (*builtin_func[j])(command, envl);
			j++;
		}
		g_vars.pid = fork();
		if (g_vars.pid == CHILD_PROCESS)
		{
			bin = bin_path(command->tokens[0], envl);
			if (bin == NULL)
				return (EXIT_FAILURE);
			execve(bin, command->tokens, env_list_to_env_array(envl));
		}
	}

	return (EXIT_SUCCESS);
}

int		spawn_proc(int in, int out, t_command *command, t_dlist envl)
{
	int		j;
	char	*bin;
	/*TEST CODE*/
	expand_env_variables_test(command, envl);
	/*TEST CODE*/
	j = 0;
	g_vars.pid = fork();
	if (g_vars.pid == CHILD_PROCESS) // Meaning we're in the child process
	{
		// redir_in_out(in, out);
		while (j < num_builtins())
		{
			if (strcmp(command->tokens[0], builtin_str[j]) == 0)
				return (*builtin_func[j])(command, envl);
			j++;
		}
		bin = bin_path(command->tokens[0], envl);
		if (bin == NULL)
			return (EXIT_FAILURE);
		execve(bin, command->tokens, env_list_to_env_array(envl));
	}
	return (EXIT_SUCCESS);
}

void	fork_pipes(t_dlist pipeline, t_dlist envl)
{
	int		fds[2];
	int		in;
	int		status;

	in = STDIN_FILENO;
	dlist_move_cursor_to_head(pipeline);
	while (pipeline->cursor_n->n != pipeline->sentinel)
	{
		// pipe(fds);
		((t_command *)pipeline->cursor_n->value)->is_only_command = FALSE;
		((t_command *)pipeline->cursor_n->value)->is_pipe = 1;
		spawn_proc(in, STDOUT_FILENO, pipeline->cursor_n->value, envl);
		// spawn_proc(in, fds[1], pipeline->cursor_n->value, envl);
		// close(fds[1]);
		// if (in != STDIN_FILENO)
		// 	close(in);
		// in = fds[0];
		dlist_move_cursor_to_next(pipeline);
	}
	spawn_proc_lcmd(in, pipeline->cursor_n->value, envl);
	// Parent Process
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_vars.exit_code = WEXITSTATUS(status);
}

void		execute_parsed_line(t_dlist parsed_line, t_dlist envl)
{
	dlist_move_cursor_to_head(parsed_line);
	while (parsed_line->cursor_n != parsed_line->sentinel)
	{
		fork_pipes(parsed_line->cursor_n->value, envl);
		dlist_move_cursor_to_next(parsed_line);
	}
	// Why do you destroy it, It was about to make me go damn crazy
	// dlist_destroy(parsed_line);
}
