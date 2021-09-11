/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_methods1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 15:55:36 by khafni            #+#    #+#             */
/*   Updated: 2021/09/11 15:55:38 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlists.h"

void	push_to_stack(t_dlist stack, void *data)
{
	if (!data)
		return ;
	dlist_move_cursor_to_tail(stack);
	dlist_insert_after_cursor(stack, data);
}

void	*pop_from_stack(t_dlist stack)
{
	void	*val;

	val = NULL;
	if (stack->len)
	{
		dlist_move_cursor_to_tail(stack);
		val = stack->cursor_p->value;
		dlist_remove_before_cursor(stack, 0);
		return (val);
	}
	return (val);
}

void	*get_stack_top_el(t_dlist stack)
{
	void	*val;

	val = NULL;
	if (stack->len)
	{
		dlist_move_cursor_to_tail(stack);
		val = stack->cursor_p->value;
		return (val);
	}
	return (val);
}
