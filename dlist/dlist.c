/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:17:36 by khafni            #+#    #+#             */
/*   Updated: 2021/03/16 12:09:42 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlists.h"

t_dlist	dlist_empty_create(t_funPtrs funPtrs)
{
	t_dlist	l;

	l = malloc(sizeof(struct s_dlist));
	l->sentinel = malloc(sizeof(struct s_dlist_cell));
	l->sentinel->n = l->sentinel;
	l->sentinel->p = l->sentinel;
	l->cursorN = l->sentinel;
	l->cursorP = l->sentinel;
	l->funPtrs.clone = funPtrs.clone;
	l->funPtrs.destroy = funPtrs.destroy;
	l->funPtrs.predicate = funPtrs.predicate;
	l->funPtrs.print = funPtrs.print;
	l->len = 0;
	return (l);
}

void	dlist_destroy(t_dlist *L_)
{
	t_dlist			L;
	t_dlist_cell	*c;
	t_dlist_cell	*next;

	L = *L_;
	c = L->sentinel->n;
	while (c != L->sentinel)
	{
		next = c->n;
		free(c);
		c = next;
	}
	free(L->sentinel);
	free(L);
	(*L_) = NULL;
}

void dlist_destroy_using_destructor(t_dlist *L_)
{
	t_dlist L;	
	t_dlist_cell *C;

	L = *L_;
	C = L->sentinel->n;	
	while (C != L->sentinel)
	{
		(*(L->funPtrs.destroy))(&(C->value));
		C = C->n;
	}
	dlist_destroy(L_);
}