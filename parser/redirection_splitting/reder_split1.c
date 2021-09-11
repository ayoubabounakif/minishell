/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reder_split1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:29:51 by khafni            #+#    #+#             */
/*   Updated: 2021/09/11 13:59:15 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	remplace_cursor_node_with_array(t_dlist l, t_arrptr arr)
{
	int	i;

	i = 0;
	dlist_remove_after_cursor(l, 1);
	while (i < arr->len)
	{
		dlist_insert_before_cursor(l, strdup(arrptr_get(arr, i)));
		i++;
	}
}

void	tokens_split_w_red(t_dlist tokens)
{	
	char		*mask;
	t_arrptr	arr;

	dlist_move_cursor_to_head(tokens);
	mask = NULL;
	if (*(char *)(tokens->cursor_n->value) == '"'
		|| *(char *)(tokens->cursor_n->value) == '\'')
		return ;
	while (tokens->cursor_n != tokens->sentinel)
	{
		mask = get_mask((char *)(tokens->cursor_n->value));
		if (is_red_cmd_non_split(tokens->cursor_n->value, mask))
		{
			arr = split_token_w_red((char *)tokens->cursor_n->value);
			remplace_cursor_node_with_array(tokens, arr);
			dlist_move_cursor_to_head(tokens);
			arrptr_destroy(arr);
		}	
		free(mask);
		dlist_move_cursor_to_next(tokens);
	}	
}
