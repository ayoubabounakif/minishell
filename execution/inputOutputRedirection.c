/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputOutputRedirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 19:09:55 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/27 19:10:05 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	implement_heredoc(char *hdoc_limit, int fd)
{
	char	*buf;

	while (420)
	{
		buf = readline("> ");
		if (strcmp(buf, hdoc_limit) == HEREDOC_DELIM)
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
		return (errno);	
	}
	implement_heredoc(rf->file_name, fd);
	close(fd);
	fd = open(template, O_RDONLY, 0644);
	unlink(template);
	*fdin = fd;
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
		if (rf->file_type == REDI_INPUT_FILE)
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
		else if (rf->file_type == REDI_HEREDOC_FILE)
		{
			if (fdin != STDIN_FILENO)
				close(fdin);
			heredoc(rf, &fdin);
		}
		if (fdin < 0 || fdout < 0)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return (errno);
		}
		i++;
	}
	if ((rf->file_type == REDI_INPUT_FILE || rf->file_type == REDI_HEREDOC_FILE)
		&& fdin > 2)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	else if ((rf->file_type == REDI_OUTPUT_FILE || rf->file_type == REDI_APPEND_FILE)
		&& fdout > 2)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	return ;
}