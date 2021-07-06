/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_methods1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:58:04 by khafni            #+#    #+#             */
/*   Updated: 2021/03/16 12:00:09 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlists.h"

void			dlist_set_after_cursor(t_dlist l, void *value, char delete)
{
	t_dlist_cell c;

	c = l->cursor_n;
	if (delete)
		(*(l->destroy))(c->value);
	c->value = value;
}

void			dlist_set_before_cursor(t_dlist l, void *value, char delete)
{
	t_dlist_cell	c;

	c = l->cursor_p;
	if (delete)
		(*(l->destroy))(c->value);
	c->value = value;
}

void			*dlist_get_after_cursor(t_dlist l, char delete)
{
	return (l->cursor_n->value);
}

void			*dlist_get_before_cursor(t_dlist l, char delete)
{
	return (l->cursor_p->value);
}

void			dlist_pushback(t_dlist l, void *value)
{
	dlist_move_cursor_to_tail(l);
	dlist_insert_before_cursor(l, value);
}