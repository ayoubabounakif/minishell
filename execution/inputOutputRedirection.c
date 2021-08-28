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

void	implement_heredoc(char *delim, int fd)
{
	char	*buf;

	while (420)
	{
		buf = readline("> ");
		if (strcmp(buf, delim) == DELIM)
		{
			free(buf);
			break ;
		}
		free(buf);
	}
	return ;
}

void	heredoc(t_redir_file rf, int *fdin)
{
	int		fd;

	fd = open("/tmp/heredoc_tmpf", O_CREAT | O_TRUNC | O_WRONLY);
	if (fd < 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(errno);	
	}
	implement_heredoc(rf->file_name, fd);
	close(fd);
	unlink("/tmp/heredoc_tmpf");
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
			exit(errno);
		}
		i++;
	}
	if (rf->file_type == REDI_INPUT_FILE && fdin > 2)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	else if (rf->file_type == REDI_OUTPUT_FILE && fdout > 2)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	else if (rf->file_type == REDI_APPEND_FILE && fdout > 2)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	return ;
}