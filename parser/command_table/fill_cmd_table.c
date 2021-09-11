/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:29:09 by khafni            #+#    #+#             */
/*   Updated: 2021/09/11 15:17:17 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	is_token_a_r_app_file(t_commands_table cmdt)
{
	t_tokens	up;		

	up = cmdt->tokens_unproccessed;
	if (up->tokens->cursor_p == up->tokens->sentinel)
		return (0);
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (ft_strnstr((char *)(up->tokens->cursor_p->value), ">>", 2))
			return (1);
		return (0);
	}		
	if (ft_strnstr((char *)(up->tokens->cursor_p->value), ">>", 2))
		return (1);
	return (0);
}

int	is_token_a_r_heredoc_file(t_commands_table cmdt)
{
	t_tokens	up;		

	up = cmdt->tokens_unproccessed;
	if (up->tokens->cursor_p == up->tokens->sentinel)
		return (0);
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (ft_strnstr((char *)(up->tokens->cursor_p->value), "<<", 2))
			return (1);
		return (0);
	}
	if (ft_strnstr((char *)(up->tokens->cursor_p->value), "<<", 2))
		return (1);
	return (0);
}

int	is_token_a_r_o_file(t_commands_table cmdt)
{
	t_tokens	up;		

	up = cmdt->tokens_unproccessed;
	if (up->tokens->cursor_p == up->tokens->sentinel)
		return (0);
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (*(char *)(up->tokens->cursor_p->value) == '>')
			return (1);
		return (0);
	}
	if (*(char *)(up->tokens->cursor_p->value) == '>'
	&& !ft_strnstr((char*)(up->tokens->cursor_p->value), ">>", 2))
		return (1);
	return (0);
}

int	is_token_a_r_i_file(t_commands_table cmdt)
{
	t_tokens	up;	

	up = cmdt->tokens_unproccessed;
	if (up->tokens->cursor_p == up->tokens->sentinel)
		return (0);
	else if (up->tokens->cursor_n == up->tokens->sentinel)
	{
		if (*(char *)(up->tokens->cursor_p->value) == '<')
			return (1);
		return (0);
	}
	if (*(char *)(up->tokens->cursor_p->value) == '<'
	&& !ft_strnstr((char*)(up->tokens->cursor_p->value), "<<", 2))
		return (1);
	return (0);
}

int	is_normal_token(t_commands_table cmdt)
{
	t_tokens	up;		

	up = cmdt->tokens_unproccessed;
	if (up->tokens_masks->cursor_p == up->tokens_masks->sentinel)
	{
		if (*(char *)(up->tokens_masks->cursor_n->value) == '>'
		|| *(char *)(up->tokens_masks->cursor_n->value) == '<')
			return (0);
		return (1);
	}	
	else if (up->tokens_masks->cursor_n == up->tokens_masks->sentinel)
	{
		if (*(char *)(up->tokens_masks->cursor_p->value) == '>'
		|| *(char *)(up->tokens_masks->cursor_p->value) == '<')
			return (0);
		return (1);
	}	
	if ((*(char *)(up->tokens_masks->cursor_p->value) == '>'
		|| *(char *)(up->tokens_masks->cursor_p->value) == '<')
		|| (*(char *)(up->tokens_masks->cursor_n->value) == '<')
		|| (*(char *)(up->tokens_masks->cursor_n->value) == '>'))
		return (0);
	return (1);
}
