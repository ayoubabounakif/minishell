/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:05:40 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/10 18:18:30 by khafni           ###   ########.fr       */
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

char	get_mask_character_helper3(t_state *state, char *s, int i)
{
	if (state->inside_dquote == 1)
		return (get_mask_char_inside_dq(state, s, i));
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
	return ('N');
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
	if (state->inside_dquote == 1 || state->env_variable == 1)
		get_mask_character_helper3(state, s, i);
	else if (s[i] == '$' || s[i] == '\'' || s[i] == '\"')
		return (get_mask_character_helper(state, s, i));
	else if (s[i] == '|' || s[i] == '>' || s[i] == '<'
		|| s[i] == ' ')
		return (get_mask_character_helper_last(s[i]));
	return ('N');
}

char	*get_mask(char *s)
{
	int		i;
	int		len;
	char	*dst;
	t_state	state;

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
