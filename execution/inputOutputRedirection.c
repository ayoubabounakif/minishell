/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputOutputRedirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 19:09:55 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/12 17:04:38 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	dupFd(int *fd, int whichFd)
{
	if (*fd > 2)
	{
		dup2(*fd, whichFd);
		close(*fd);
	}
}

void	searchForLastIn(t_commands_table command, int *fdin)
{
	int				i;
	int				wasHere;
	char			*tmpNameHolder;
	t_redir_file	rf;

	i = 0;
	wasHere = 0;
	tmpNameHolder = NULL;
	while (i < command->redir_files->len)
	{
		rf = arrptr_get(command->redir_files, i);
		if (rf->file_type == REDI_INPUT_FILE
			|| rf->file_type == REDI_HEREDOC_FILE)
		{
			wasHere = 1;
			tmpNameHolder = rf->file_name;
		}
		i++;
	}
	if (wasHere)
		dupFd(fdin, STDIN_FILENO);
	return ;
}

void	searchForLastOut(t_commands_table command, int *fdout)
{
	int				i;
	int				wasHere;
	char			*tmpNameHolder;
	t_redir_file	rf;

	i = 0;
	wasHere = 0;
	tmpNameHolder = NULL;
	while (i < command->redir_files->len)
	{
		rf = arrptr_get(command->redir_files, i);
		if (rf->file_type == REDI_OUTPUT_FILE
			|| rf->file_type == REDI_APPEND_FILE)
		{
			wasHere = 1;
			tmpNameHolder = rf->file_name;
		}
		i++;
	}
	if (wasHere)
		dupFd(fdout, STDOUT_FILENO);
	return ;
}

void	mainIOLoop(t_redir_file rf, int *fdin, int *fdout)
{
	if (rf->file_type == REDI_INPUT_FILE
		|| rf->file_type == REDI_HEREDOC_FILE)
	{
		if (*fdin != STDIN_FILENO)
			close(*fdin);
		*fdin = open(rf->file_name, O_RDONLY, 0644);
	}
	else if (rf->file_type == REDI_OUTPUT_FILE)
	{
		if (*fdout != STDOUT_FILENO)
			close(*fdout);
		*fdout = open(rf->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (rf->file_type == REDI_APPEND_FILE)
	{
		if (*fdout != STDOUT_FILENO)
			close(*fdout);
		*fdout = open(rf->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if ((*fdin < 0 || *fdout < 0) && rf->file_type != REDI_HEREDOC_FILE)
	{
		printErrorMessage(rf->file_name, "");
		g_vars.exit_code = EXIT_FAILURE;
		exit(g_vars.exit_code);
	}
}

void	inputOutputRedirection(t_commands_table command)
{
	int				i;
	int				fdin;
	int				fdout;
	t_redir_file	rf;

	fdin = STDIN_FILENO;
	fdout = STDOUT_FILENO;
	i = 0;
	while (i < command->redir_files->len)
	{
		rf = arrptr_get(command->redir_files, i);
		mainIOLoop(rf, &fdin, &fdout);
		i++;
	}
	searchForLastIn(command, &fdin);
	searchForLastOut(command, &fdout);
	return ;
}
