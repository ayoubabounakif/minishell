/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:49:10 by aabounak          #+#    #+#             */
/*   Updated: 2021/03/31 17:49:11 by aabounak         ###   ########.fr       */
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

int (*builtin_func[])(char **, t_dlist) = {
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

char *bin_path(char *cmd, char **envp)
{
	t_dlist envl;
	t_env *_420sh_env;
	int bin_fd;
	char *path;
	char *bin_path;
	char **split_path;
	int i;

	i = 0;
	bin_path = NULL;
	envl = get_envs(envp);
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
		ft_putstr_fd("_420sh: ", STDERR);
		ft_putstr_fd(cmd, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
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
	ft_putstr_fd("_420sh: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": command not found\n", STDERR);
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

/*
** TO-DO: Get pipes to work with builtins and hunt leaks
**/

int execute_last_command(int in, int i, t_command *command, char **envp)
{
	// t_dlist	env_list;
	// int		j;
	char	*path;

	// BUILTINNNNNNNNNNS LAST COMMAND
	// env_list = get_envs(envp);
	// j = 0;
	// while (j < num_builtins())
	// {
	// 	if (strcmp(command->tokens[0], builtin_str[j]) == 0)
	// 		return (*builtin_func[j])(command->tokens, env_list);
	// 	j++;
	// }
	path = bin_path(command->tokens[0], envp);
	if (path == NULL)
		return (0);
	// if (in != STDIN)
	// 	close(in);
	g_vars.pid = fork();
	if (g_vars.pid == CHILD_PROCESS)
	{
		if (in != STDIN)
		{
			dup2(in, STDIN);
			close(in);
		}
		execve(path, command->tokens, envp);
	}
	return (1);
}

int execute_command(int in, int out, t_command *command, char **envp)
{
	t_dlist	env_list;
	int		j;
	char	*path;

	env_list = get_envs(envp);
	j = 0;
	while (j < num_builtins())
	{
		if (strcmp(command->tokens[0], builtin_str[j]) == 0)
		{
			g_vars.pid = fork();
			if (g_vars.pid == CHILD_PROCESS)
			{
				redir_in_out(in, out);
				return (*builtin_func[j])(command->tokens, env_list);
			}
		}
		j++;
	}
	path = bin_path(command->tokens[0], envp);
	if (path == NULL)
		return (0);
	g_vars.pid = fork();
	if (g_vars.pid == CHILD_PROCESS) // Meaning we're in the child process
	{
		redir_in_out(in, out);
		execve(path, command->tokens, envp);
	}
	return (1);
}

int			execute_pipeline(t_dlist pipeline, char **envp)
{
	int i;
	int fds[2];
	int in;
	int	status;

	in = STDIN;
	i = 0;
	dlist_move_cursor_to_head(pipeline);
	while (pipeline->cursor_n->n != pipeline->sentinel)
	{
		pipe(fds);
		execute_command(in, fds[1], pipeline->cursor_n->value, envp);
		close(fds[1]);
		if (in != STDIN)
			close(in);
		in = fds[0];
		dlist_move_cursor_to_next(pipeline);
	}
	execute_last_command(in, i, pipeline->cursor_n->value, envp);
	// Parent Process
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_vars.exit_code = WEXITSTATUS(status);
	return (status);
}

void		execute_parsed_line(t_dlist parsed_line, char **envp)
{
	dlist_move_cursor_to_head(parsed_line);
	while (parsed_line->cursor_n != parsed_line->sentinel)
	{
		execute_pipeline(parsed_line->cursor_n->value, envp);
		dlist_move_cursor_to_next(parsed_line);
	}
}
