/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_methods4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:39:49 by khafni            #+#    #+#             */
/*   Updated: 2021/04/16 13:44:28 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlists.h"

void	dlist_insert_after_cursor_and_jump(t_dlist l, void *value)
{
	dlist_insert_after_cursor(l, value);	
	dlist_move_cursor_to_next(l);
}

void	dlist_insert_before_cursor_and_jump(t_dlist l, void *value)
{
	dlist_insert_before_cursor(l, value);
	dlist_move_cursor_to_previous(l);
}


void	dlist_print(t_dlist L, char *sep)
 {
	t_dlist_cell *C;

	if (L->funPtrs.print == NULL)
		return ;
	printf("L(\n");
	C = L->sentinel->n;
	while (C != L->sentinel)
	{
		(*(L->funPtrs.print)) (C->value);
		printf("%s", sep);
		C = C->n;
	}
	printf(")");
 }

int		dlist_length(t_dlist L)
{
	return (L->len);
}

char			is_dlist_empty(t_dlist L)
{
	return (L->len == 0);
}