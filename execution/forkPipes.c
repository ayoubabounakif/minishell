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

int	checkExecutable(char *token)
{
	int	fd;

	fd = open(token, O_RDONLY);
	if (fd < 0)
		return (0);
	return (1);
}

void	forkPipes(t_dlist pipeline, t_dlist envl)
{
	int		pipeFds[2];
	int		in;
	int		ret;
	int		status;

	in = STDIN_FILENO;
	dlist_move_cursor_to_head(pipeline);
	while (pipeline->cursor_n->n != pipeline->sentinel)
	{
		ret = isBuiltin(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0]);
		if (ret != TRUE)
		{
			if (!checkExecutable(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0]))
			{
				if (((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] == NULL)
					return ;
				((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] = binPath(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0], envl);
				if (((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] == NULL)
				{
					printErrorMessage(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0], "");
					g_vars.exit_code = 127;
					return ;
				}
			}
		}
		pipe(pipeFds);
		spawnProc(in, pipeFds, pipeline->cursor_n->value, envl);
		if (pipeFds[WRITE] > 2)
			close(pipeFds[WRITE]);
		if (in != STDIN_FILENO)
			close(in);
		in = pipeFds[READ];
		dlist_move_cursor_to_next(pipeline);
	}
	ret = isBuiltin(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0]);
	if (ret != TRUE)
	{
		if (!checkExecutable(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0]))
		{
			if (((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] == NULL)
				return ;
			((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] = binPath(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0], envl);
			if (((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0] == NULL)
			{
				printErrorMessage(((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0], "");
				g_vars.exit_code = 127;
				return ;
			}
		}
	}
	spawnLastProc(in, pipeFds, pipeline->cursor_n->value, envl);
	if (in != STDIN_FILENO)
		close(in);
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			g_vars.exit_code = WEXITSTATUS(status);
}
