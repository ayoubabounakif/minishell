/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputOutputRedirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 19:09:55 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/08 16:48:51 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	searchForLastIn(t_commands_table command, int *fdin)
{
	int				i = 0;
	int				wasHere = 0;
	char			*tmpNameHolder;
	t_redir_file	rf;

	tmpNameHolder = NULL;
	while (i < command->redir_files->len)
	{
		rf = arrptr_get(command->redir_files, i);
		if (rf->file_type == REDI_INPUT_FILE || rf->file_type == REDI_HEREDOC_FILE)
		{
			wasHere = 1;
			tmpNameHolder = rf->file_name;
		}
		i++;
	}
	if (wasHere)
	{
		if (*fdin > 2)
		{
			ft_putendl_fd("PUSSY", STDERR_FILENO);
			dup2(*fdin, STDIN_FILENO);
			close(*fdin);
		}
	}
	return ;
}

void	searchForLastOut(t_commands_table command, int *fdout)
{
	int				i = 0;
	int				wasHere = 0;
	char			*tmpNameHolder;
	t_redir_file	rf;

	tmpNameHolder = NULL;
	while (i < command->redir_files->len)
	{
		rf = arrptr_get(command->redir_files, i);
		if (rf->file_type == REDI_OUTPUT_FILE || rf->file_type == REDI_APPEND_FILE)
		{
			wasHere = 1;
			tmpNameHolder = rf->file_name;
		}
		i++;
	}
	if (wasHere)
	{
		if (*fdout > 2)
		{
			ft_putendl_fd("another OUT PUSSY", STDERR_FILENO);
			dup2(*fdout, STDOUT_FILENO);
			close(*fdout);
		}
	}
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
		if ((fdin < 0 || fdout < 0) && rf->file_type != REDI_HEREDOC_FILE)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			g_vars.exit_code = 1;
			exit(g_vars.exit_code);
		}
		i++;
	}
	searchForLastIn(command, &fdin);
	searchForLastOut(command, &fdout);
	return ;
}
