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

# include "../includes/minishell.h"

void		executeParsedLine(t_dlist parsed_line, t_dlist envl)
{
	dlist_move_cursor_to_head(parsed_line);
	while (parsed_line->cursor_n != parsed_line->sentinel)
	{
		forkPipes(parsed_line->cursor_n->value, envl);
		dlist_move_cursor_to_next(parsed_line);
	}
}
