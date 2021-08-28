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

void	dlist_insert_after_cursor(t_dlist l, void *value)
{
	t_dlist_cell	*new;

	new = malloc(sizeof(struct s_dlist_cell));
	new->value = value;
	new->p = l->cursorP;
	new->n = l->cursorN;
	l->cursorN->p = new;
	l->cursorP->n = new;
	l->cursorN = new;
	l->len++;
}

void	dlist_insert_before_cursor(t_dlist L, void *value)
{
	t_dlist_cell	*new_cell;

	new_cell = malloc(sizeof(struct s_dlist_cell));
	new_cell->value = value;
	new_cell->n = L->cursorN;
	new_cell->p = L->cursorP;
	L->cursorP->n = new_cell;
	L->cursorN->p = new_cell;
	L->cursorP = new_cell;
	L->len++;
}

void	dlist_remove_after_cursor(t_dlist l, char delete)
{
	t_dlist_cell	*n;
	t_dlist_cell	*p;

	n = l->cursorN;
	p = l->cursorP;
	p->n = n->n;
	n->n->p = p;
	l->cursorN = n->n;
	if (delete)
		(*(l->funPtrs.destroy))((n->value));
	free(n);
	l->len--;
}

void	dlist_remove_before_cursor(t_dlist l, char delete)
{
	t_dlist_cell	*n;
	t_dlist_cell	*p;

	n = l->cursorN;
	p = l->cursorP;
	n->p = p->p;
	p->p->n = n;
	l->cursorP = p->p;
	if (delete)
		(*(l->funPtrs.destroy))(p->value);
	free(p);
	l->len--;
}
