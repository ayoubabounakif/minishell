/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeParsedLine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:28:18 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/27 17:28:37 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	testForUppercaseBuiltins(t_dlist pipeline)
{
	char	*token;

	dlist_move_cursor_to_head(pipeline);
	token = ((t_commands_table)pipeline->cursor_n->value)->tokens_simpl[0];
	if (token)
	{
		if (isBuiltin(token) == UPPERCASE_BUILTINS)
		{
			printErrorMessage(token, "");
			g_vars.exit_code = 127;
			return (UPPERCASE_BUILTINS);
		}
	}
	return (EXIT_SUCCESS);
}

void	executeParsedLine(t_dlist parsed_line, t_dlist envl)
{	
	if (testForUppercaseBuiltins(parsed_line) == UPPERCASE_BUILTINS)
		;
	else
		forkPipes(parsed_line, envl);
}
