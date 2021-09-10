/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:54:31 by khafni            #+#    #+#             */
/*   Updated: 2021/09/10 11:10:58 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_one_of_the_candtions(char c)
{
	if (c == '$' || c == '\''
		|| c == '"' || c == ';'
		|| c == '<' || c == '>'
		|| c == ' ' || c == 'W')
		return (1);
	return (0);
}

char	get_mask_c_helper2(t_state *state, char *s, int i)
{
	if (state->env_variable == 1)
	{
		if (ft_isalnum(s[i]) || s[i] == '?')
		{
			if (s[i] == '?')
				state->env_variable = 0;
			return ('V');
		}
		if (s[i] == '$')
			return ('$');
		state->env_variable = 0;
	}
	if (is_one_of_the_candtions(s[i]))
		return (get_mask_c_helper(state, s, i));
	return ('N');
}

char	get_mask_c_helper(t_state *state, char *s, int i)
{
	if (s[i] == '$')
	{
		state->env_variable = 1;
		return ('$');
	}
	else if (s[i] == '\'')
	{
		state->inside_squote = 1;
		return ('\'');
	}
	else if (s[i] == '\"')
	{
		state->inside_dquote = 1;
		return ('\"');
	}
	else if (s[i] == '|')
		return ('|');
	else if (s[i] == '>')
		return ('>');
	else if (s[i] == '<')
		return ('<');
	else if (s[i] == ' ')
		return ('W');
	return ('N');
}
