/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reder_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:29:39 by khafni            #+#    #+#             */
/*   Updated: 2021/09/04 17:47:43by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int				is_red_cmd_non_split(char *token_)
{
	char *token;	
	int i;
	int r;
	int al;

	i = 0;
	r = 0;
	al = 0;
	token = (char*)token_;	
	while (token[i])
	{
		if (token[i] == '>' || token[i] == '<')
			r = 1;
		else
			al = 1;	
		i++;
	}
	if (r == 1 && al == 1)
		return (1);
	else
		return (0);
}

void			split_token_w_red_help(char *token, int *i, t_arrptr arr)
{
	t_rstr rs;

	rs = rstr_create(1);
	while (token[*i] && (token[*i] == '>' || token[*i] == '<'))
		rstr_add(rs, token[(*i)++]);
	if (rs->len)
		arrptr_add(arr, rstr_to_cstr(rs));
	rstr_clear(rs);
	while (token[*i] && (token[*i] != '>' && token[*i] != '<'))
		rstr_add(rs, token[(*i)++]);
	if (rs->len)
		arrptr_add(arr, rstr_to_cstr(rs));
	rstr_destroy(rs);
}

t_arrptr		split_token_w_red(char *token)
{
	t_rstr rs;
	t_arrptr	arr;
	int			i;

	i = 0;
	rs = rstr_create(0);
	arr = empty_arrptr_create(free);
	while(token[i])
	{
		if (token[i] != '>' && token[i] != '<')
		{
			rstr_add(rs, token[i]);
		}
		else if (token[i] == '>' || token[i] == '<')
		{
			if (rs->len)
				arrptr_add(arr, rstr_to_cstr(rs));
			split_token_w_red_help(token, &i, arr);
		rstr_clear(rs);
			continue ;
		}
		i++;
	}
	rstr_destroy(rs);
	return (arr);
}

void remplace_cursor_node_with_array(t_dlist l, t_arrptr arr)
{
	int i = 0;

	dlist_remove_after_cursor(l, 1);
	 	while (i < arr->len)
		{
			dlist_insert_before_cursor(l, strdup(arrptr_get(arr, i)));
			i++;
		}
}

void			tokens_split_w_red(t_dlist tokens)
{	
	char *mask;

	dlist_move_cursor_to_head(tokens);
	mask = get_mask((char*)(tokens->cursor_n->value));
	if (*(char*)(tokens->cursor_n->value) == '"'
	|| *(char*)(tokens->cursor_n->value) == '\'')
		return ;
    while (tokens->cursor_n != tokens->sentinel) 
    {
		if (is_red_cmd_non_split(tokens->cursor_n->value))
		{
			t_arrptr arr =  split_token_w_red((char*)tokens->cursor_n->value);
			remplace_cursor_node_with_array(tokens, arr);
			dlist_move_cursor_to_head(tokens);
			arrptr_destroy(arr);
		}	
        dlist_move_cursor_to_next(tokens);	
	}
 }