/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_methods2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:06:00 by khafni            #+#    #+#             */
/*   Updated: 2021/05/22 18:45:01 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlists.h"

void	dlist_move_cursor_to_head(t_dlist l)
{
	l->cursorP = l->sentinel;
	l->cursorN = l->sentinel->n;
}

void	dlist_move_cursor_to_tail(t_dlist l)
{
	l->cursorN = l->sentinel;
	l->cursorP = l->sentinel->p;
}

void	dlist_move_cursor_to_next(t_dlist l)
{
	if (l->cursorN != l->sentinel)
	{
		l->cursorP = l->cursorN;
		l->cursorN = l->cursorN->n;
	}
}

void	dlist_move_cursor_to_previous(t_dlist l)
{
	if (l->cursorP != l->sentinel)
	{
		l->cursorN = l->cursorP;
		l->cursorP = l->cursorP->p;
	}
}
