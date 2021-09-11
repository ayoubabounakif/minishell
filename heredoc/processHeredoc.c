/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processHeredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:26:01 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/11 16:26:20 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

void	processHeredoc(t_dlist pipeline)
{
	dlist_move_cursor_to_head(pipeline);
	while (pipeline->cursor_n != pipeline->sentinel)
	{
		heredoc_for_one_cmd_table(pipeline->cursor_n->value);
		dlist_move_cursor_to_next(pipeline);
	}
	return ;
}
