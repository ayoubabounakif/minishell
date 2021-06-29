/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkPipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:20:19 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/27 17:20:37 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	forkPipes(t_dlist pipeline, t_dlist envl)
{
	int		pipeFds[2];
	int		in;
	int		status;

	in = STDIN_FILENO;
	dlist_move_cursor_to_head(pipeline);
	while (pipeline->cursor_n->n != pipeline->sentinel)
	{
		pipe(pipeFds);
		((t_command *)pipeline->cursor_n->value)->is_only_command = FALSE;
		((t_command *)pipeline->cursor_n->value)->is_pipe = TRUE;
		spawnProc(in, pipeFds, pipeline->cursor_n->value, envl);
		if (pipeFds[WRITE] > 2)
			close(pipeFds[WRITE]);
		in = pipeFds[READ];
		dlist_move_cursor_to_next(pipeline);
	}
	spawnLastProc(in, pipeFds, pipeline->cursor_n->value, envl);
	if (in != STDIN_FILENO)
		close(in);
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_vars.exit_code = WEXITSTATUS(status);
}
