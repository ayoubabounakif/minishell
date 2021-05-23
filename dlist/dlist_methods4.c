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

void			dlist_insert_after_cursor_n_move_n(t_dlist l, void *value)
{
	dlist_insert_after_cursor(l, value);
	dlist_move_cursor_to_next(l);
}

void			dlist_insert_before_cursor_n_move_p(t_dlist l, void *value)
{
	dlist_insert_before_cursor(l, value);
	dlist_move_cursor_to_previous(l);
}
