/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_methods3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:58:04 by khafni            #+#    #+#             */
/*   Updated: 2021/06/28 06:54:35 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlists.h"

void	dlist_set_after_cursor(t_dlist l, void *value, char delete)
{
	if (l->cursorN == l->sentinel)
		return ;
	if (delete)
		(*(l->funPtrs.destroy))(&(l->cursorP->value));
	l->cursorN->value = value;
}

void	dlist_set_before_cursor(t_dlist l, void *value, char delete)
{
	if (l->cursorP == l->sentinel)	
		return ;
	if (delete)
		(*(l->funPtrs.destroy))(&(l->cursorP->value));
	l->cursorP->value = value;
}

void	*dlist_get_after_cursor(t_dlist l)
{
	if (l->cursorN == l->sentinel)
		return (NULL);
	return (l->cursorN->value);
}

void	*dlist_get_before_cursor(t_dlist l)
{
	if (l->cursorP == l->sentinel)
		return (NULL);
	return (l->cursorP->value);
}

void	dlist_pushback(t_dlist l, void *value)
{
	dlist_move_cursor_to_tail(l);
	dlist_insert_before_cursor(l, value);
}
