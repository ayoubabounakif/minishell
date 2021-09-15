/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:05:40 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/15 14:46:44 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_states(t_state *state)
{
	state->skip = 0;
	state->inside_squote = 0;
	state->inside_dquote = 0;
	state->env_variable = 0;
	state->env_variable_dq = 0;
}

char	get_mask_character_helper2(t_state *state, char *s, int i)
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
	return ('N');
}

char	get_mask_character_helper1(t_state *state, char *s, int i)
{
	if (s[i] == '?')
		state->env_variable = 0;
	return ('V');
}

char	get_mask_character(t_state *state, char *s, int i)
{
	if (state->inside_squote == 1)
	{
		if (s[i] == '\'')
		{
			state->inside_squote = 0;
			return ('\'');
		}
		return ('L');
	}
	if (state->inside_dquote == 1)
		return (get_mask_char_inside_dq(state, s, i));
	if (state->env_variable == 1)
	{
		if (ft_isalnum(s[i]) || s[i] == '?' || s[i] == '_')
			return (get_mask_character_helper1(state, s, i));
		if (s[i] == '$')
			return ('$');
		state->env_variable = 0;
	}
	else if (s[i] == '$' || s[i] == '\'' || s[i] == '\"' )
		return (get_mask_character_helper2(state, s, i));
	else if (s[i] == '|' || s[i] == '>' || s[i] == '<'
		|| s[i] == ' ')
		return (get_mask_character_helper_last(s[i]));
	return ('N');
}

char	*get_mask(char *s)
{
	int			i;
	int			len;
	char		*dst;
	t_state		state;

	i = 0;
	len = ft_strlen(s);
	init_states(&state);
	dst = (char *)malloc(sizeof(char) + len + 1);
	while (i < len && s[i] != '\0')
	{
		dst[i] = get_mask_character(&state, s, i);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
