/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkPipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:34:34 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/16 13:50:12 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parentProcess(int *in)
{
	int	status;

	if (*in != STDIN_FILENO)
		close(*in);
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_vars.exit_code = WEXITSTATUS(status);
}

void	multiPurposeCheck(char **token, t_dlist envl)
{
	int	ret;

	ret = isBuiltin(*token);
	if (ret != TRUE)
	{
		if (!checkExecutable(*token))
		{
			if (*token != NULL)
				*token = binPath(*token, envl);
		}
	}
}

void	forkPipes(t_dlist pipel, t_dlist envl)
{
	int		pipeFds[2];
	int		in;

	g_vars.noneOfUrBusiness = 0;
	in = STDIN_FILENO;
	dlist_move_cursor_to_head(pipel);
	while (pipel->cursor_n->n != pipel->sentinel)
	{
		multiPurposeCheck(
			&((t_commands_table)pipel->cursor_n->value)->tokens_simpl[0],
			envl);
		pipe(pipeFds);
		spawnProc(in, pipeFds, pipel->cursor_n->value, envl);
		if (pipeFds[WRITE] > 2)
			close(pipeFds[WRITE]);
		if (in != STDIN_FILENO)
			close(in);
		in = pipeFds[READ];
		g_vars.noneOfUrBusiness = YES_PIPE;
		dlist_move_cursor_to_next(pipel);
	}
	multiPurposeCheck(
		&((t_commands_table)pipel->cursor_n->value)->tokens_simpl[0], envl);
	spawnLastProc(in, pipeFds, pipel->cursor_n->value, envl);
	parentProcess(&in);
}
