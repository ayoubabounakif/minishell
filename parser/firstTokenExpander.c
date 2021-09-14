/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstTokenExpander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:01:20 by khafni            #+#    #+#             */
/*   Updated: 2021/09/14 18:33:03 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_first_token_devided(char **tokens_simpl)
{
	char	*first_token;
	char	*mask;
	int		i;

	first_token = tokens_simpl[0];
	if (tokens_simpl[0] == NULL)
		return (0);
	mask = get_mask(first_token);
	i = 0;
	if (cstr_lookup(mask, "WN"))
	{
		free(mask);
		return (1);
	}
	free(mask);
	return (0);
}

t_arrptr	token_array_clone(void *data)
{
	t_commands_table	cmd;
	t_arrptr			arr;
	int					i;

	cmd = data;
	arr = empty_arrptr_create(free);
	i = 0;
	while (cmd->tokens_simpl[i])
	{
		arrptr_add(arr, ft_strdup(cmd->tokens_simpl[i]));
		i++;
	}
	return (arr);
}

void	carray_to_carr(char ***tokens_simpl_,
	t_arrptr changed_arr, t_commands_table cmd)
{
	char	**tokens_simpl;
	int		i;

	i = 0;
	tokens_simpl = *tokens_simpl_;
	while (tokens_simpl[i])
	{
		free(tokens_simpl[i]);
		i++;
	}
	free(tokens_simpl);
	i = 0;
	tokens_simpl = malloc(sizeof(char *) * (changed_arr->len + 1));
	while (i < changed_arr->len)
	{
		tokens_simpl[i] = ft_strdup(arrptr_get(changed_arr, i));
		i++;
	}	
	tokens_simpl[i] = NULL;
	cmd->tokens_simpl = tokens_simpl;
}

void	token_array_changer(void *data)
{
	t_commands_table	cmd;
	t_arrptr			cloned_arr;
	t_arrptr			changed_arr;
	int					i;

	cmd = data;
	cloned_arr = token_array_clone(data);
	changed_arr = first_token_changer(cloned_arr);
	i = 1;
	while (i < cloned_arr->len)
	{
		arrptr_add(changed_arr, ft_strdup(arrptr_get(cloned_arr, i)));
		i++;
	}
	carray_to_carr(&(cmd->tokens_simpl), changed_arr, cmd);
	arrptr_destroy(cloned_arr);
	arrptr_destroy(changed_arr);
}

void	firstTokenExpander(t_dlist pDataL)
{
	t_commands_table	cmd;

	dlist_move_cursor_to_head(pDataL);
	while (pDataL->cursor_n != pDataL->sentinel)
	{
		cmd = pDataL->cursor_n->value;
		if (is_first_token_devided(cmd->tokens_simpl))
			token_array_changer(pDataL->cursor_n->value);
		dlist_move_cursor_to_next(pDataL);
	}
	dlist_move_cursor_to_head(pDataL);
	while (pDataL->cursor_n != pDataL->sentinel)
	{
		cmd = pDataL->cursor_n->value;
		dlist_move_cursor_to_next(pDataL);
	}
}
