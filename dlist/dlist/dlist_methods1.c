/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_methods1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:09:06 by khafni            #+#    #+#             */
/*   Updated: 2021/03/28 17:58:50 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlists.h"

void			dlist_insert_after_cursor(t_dlist l, void *value)
{
	t_dlist_cell	new;

	new = malloc(sizeof(struct s_dlist_cell));
	new->value = value;
	new->p = l->cursor_p;
	new->n = l->cursor_n;
	l->cursor_n->p = new;
	l->cursor_p->n = new;
	l->cursor_n = new;
	l->len++;
}
 
void			dlist_insert_before_cursor(t_dlist l, void *value)
{
	t_dlist_cell new;

	new = malloc(sizeof(struct s_dlist_cell));
	new->value = value;
	new->p = l->cursor_p;
	new->n = l->cursor_n;
	l->cursor_n->p = new;
	l->cursor_p->n = new;
	l->cursor_p = new;
	l->len++;
}

void			dlist_remove_after_cursor(t_dlist l, char delete)
{
	t_dlist_cell n;
	t_dlist_cell p;

	n = l->cursor_n;
	p = l->cursor_p;
	p->n = n->n;
	n->n->p = p;
	l->cursor_n = n->n;
	if (delete)
		(*(l->destroy)) ((n->value));
	free(n);
	l->len--;
}
void			dlist_remove_before_cursor(t_dlist l, char delete)
{
	t_dlist_cell n;
	t_dlist_cell p;

	n = l->cursor_n;
	p = l->cursor_p;
	n->p = p->p;
	p->p->n = n;	
	l->cursor_p = p->p;
	if (delete)
		(*(l->destroy))(p->value);
	free(p);
	l->len--;
}