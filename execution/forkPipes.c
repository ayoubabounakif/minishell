/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkPipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:20:19 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/12 16:28:00by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parentProcess(void)
{
	int	status;
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_vars.exit_code = WEXITSTATUS(status);
}

/* void	mainLoop(t_dlist pipeline, int *ret, int *in, t_dlist envl)
{
	ret = isBuiltin(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0]);
	if (ret != TRUE)
	{
		if (!checkExecutable(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0]))
		{
			if (((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] != NULL)
				((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] = binPath(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0], envl, pipeline->cursor_n->value);
		}
	}
	pipe(pipeFds);
	spawnProc(in, pipeFds, pipeline->cursor_n->value, envl);
	if (pipeFds[WRITE] > 2)
		close(pipeFds[WRITE]);
	if (in != STDIN_FILENO)
		close(in);
	in = pipeFds[READ];
} */

void	forkPipes(t_dlist pipeline, t_dlist envl)
{
	// int		status;
	int		pipeFds[2];
	int		in;
	int		ret;

	in = STDIN_FILENO;
	dlist_move_cursor_to_head(pipeline);
	while (pipeline->cursor_n->n != pipeline->sentinel)
	{
/* 		ret = isBuiltin(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0]);
		if (ret != TRUE)
		{
			if (!checkExecutable(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0]))
			{
				if (((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] != NULL)
					((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] = binPath(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0], envl, pipeline->cursor_n->value);
			}
		}
		pipe(pipeFds);
		spawnProc(in, pipeFds, pipeline->cursor_n->value, envl);
		if (pipeFds[WRITE] > 2)
			close(pipeFds[WRITE]);
		if (in != STDIN_FILENO)
			close(in);
		in = pipeFds[READ]; */
		dlist_move_cursor_to_next(pipeline);
	}
	ret = isBuiltin(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0]);
	if (ret != TRUE)
	{
		if (!checkExecutable(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0]))
		{
			if (((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] != NULL)
				((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] = binPath(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0], envl, pipeline->cursor_n->value);
		}
	}
	spawnLastProc(in, pipeFds, pipeline->cursor_n->value, envl);
	if (in != STDIN_FILENO)
		close(in);
	// parentProcess();
/* 	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_vars.exit_code = WEXITSTATUS(status); */
}
