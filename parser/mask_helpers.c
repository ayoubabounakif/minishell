/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:54:31 by khafni            #+#    #+#             */
/*   Updated: 2021/09/15 14:47:45 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	get_mask_char_inside_dq(t_state *state, char *s, int i)
{
	if (state->env_variable_dq == 1)
	{
		if (ft_isalnum(s[i]) || s[i] == '?' || s[i] == '_')
		{
			if (s[i] == '?' || s[i] == ' ')
				state->env_variable_dq = 0;
			return ('V');
		}
		else if (s[i] == ' ')
		{
			state->env_variable_dq = 0;
			return (' ');
		}
	}
	if (s[i] == '$')
	{
		state->env_variable_dq = 1;
		return ('$');
	}
	if (s[i] == '\"')
	{
		state->inside_dquote = 0;
		return ('\"');
	}
	return ('S');
}

char	get_mask_character_helper_last(char c)
{
	if (c == ';')
		return (';');
	else if (c == '|')
		return ('|');
	else if (c == '>')
		return ('>');
	else if (c == '<')
		return ('<');
	else if (c == ' ')
		return ('W');
	return ('N');
}

void	destroy_mask(char **mask_)
{
	if (*mask_)
		free(*mask_);
	*mask_ = NULL;
}
