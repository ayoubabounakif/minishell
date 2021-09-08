/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputOutputRedirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 19:09:55 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/08 13:06:59 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	implement_heredoc(char *hdoc_delim, int fd)
{
	char	*buf;

	while (420)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		if (strcmp(buf, hdoc_delim) == HEREDOC_DELIM)
		{
			free(buf);
			break ;
		}
		ft_putendl_fd(buf, fd);
		free(buf);
	}
	return ;
}

int		ft_mkstemp(char *template)
{
	int	seed;
	int	pipeFds[2];
	int	n;
	int	i = 0;
	pid_t	pid;

	while (template[i])
	{
		if (template[i] == 'X')
		{
			pipe(pipeFds);
			pid = fork();
			if (pid == CHILD)
			{
				close(pipeFds[READ]);
				dup2(pipeFds[WRITE], STDOUT_FILENO);
				execve("./execution/randNG/randNGpgm", NULL, NULL);
			}
			close(pipeFds[WRITE]);
			read(pipeFds[READ], &n, 1);
			template[i] = n;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	heredoc(t_redir_file rf, int *fdin)
{
	int		fd;
	char	template[21];

	ft_memset(template, 0, sizeof(template));
	ft_strlcpy(template,"/tmp/heredoc-XXX", 21);

	ft_putendl_fd(template, STDOUT_FILENO);

	ft_mkstemp(template);

	ft_putendl_fd(template, STDOUT_FILENO);
	
	fd = open(template, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	implement_heredoc(rf->file_name, fd);
	close(fd);
	fd = open(template, O_RDONLY, 0644);
	unlink(template);
	*fdin = fd;
	return ;
}

void	searchForLastInAndLastOut(t_commands_table command, char whichOne, int *fdin)
{
	int				i = 0;
	char			*tmpNameHolder;

	t_redir_file	rf;

	while (i < command->redir_files->len)
	{
		if (rf->file_type == REDI_INPUT_FILE || rf->file_type == REDI_HEREDOC_FILE)
			tmpNameHolder = ft_strdup(rf->file_name);
		i++;
	}
	ft_putstr_fd("Last IN_FILENO: ", STDERR_FILENO);
	ft_putstr_fd(tmpNameHolder, STDERR_FILENO);
	return ;
}

void	inputOutputRedirection(t_commands_table command)
{
	int i;
	int	fdin;
	int	fdout;
	t_redir_file rf;

	fdin = STDIN_FILENO;
	fdout = STDOUT_FILENO;
	i = 0;
	while (i < command->redir_files->len)
	{
		rf = arrptr_get(command->redir_files, i);
		if (rf->file_type == REDI_INPUT_FILE || rf->file_type == REDI_HEREDOC_FILE)
		{
			if (fdin != STDIN_FILENO)
				close(fdin);
			fdin = open(rf->file_name, O_RDONLY, 0644);
		}
		else if (rf->file_type == REDI_OUTPUT_FILE)
		{
			if (fdout != STDOUT_FILENO)
				close(fdout);
			fdout = open(rf->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (rf->file_type == REDI_APPEND_FILE)
		{
			if (fdout != STDOUT_FILENO)
				close(fdout);
			fdout = open(rf->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		// if (fdin < 0 || fdout < 0)
		// {
		// 	ft_utendl_fd(strerror(errno), STDERR_FILENO);
		// 	g_vars.exit_code = 1;
		// 	exit(g_vars.exit_code);
		// }
		i++;
	}
	searchForLastInAndLastOut(command, REDI_INPUT_FILE, &fdin);
	exit(111);
	if ((rf->file_type == REDI_INPUT_FILE || rf->file_type == REDI_HEREDOC_FILE)
		&& fdin > 2)
	{
		ft_putendl_fd("PUSSY", STDERR_FILENO);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	else if ((rf->file_type == REDI_OUTPUT_FILE || rf->file_type == REDI_APPEND_FILE)
		&& fdout > 2)
	{
		ft_putendl_fd("another OUT PUSSY", STDERR_FILENO);
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	return ;
}