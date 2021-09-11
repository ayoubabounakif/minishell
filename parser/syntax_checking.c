/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:19:42 by khafni            #+#    #+#             */
/*   Updated: 2021/09/11 08:12:32 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_syx_check	syntax_check_create(void)
{
	static t_syx_check	syx = NULL;

	if (syx == NULL)
	{
		syx = malloc(sizeof(struct s_syntax));
		syx->is_error = 0;
		syx->error_message = NULL;
	}
	return (syx);
}

void	syntax_destroy(t_syx_check sx)
{
	if (sx->error_message)
		free(sx->error_message);
	free (sx);
}

void	syntax_set_error(t_syx_check sx, char *err_message)
{
	if (!sx->is_error)
	{
		sx->is_error = 1;
		sx->error_message = ft_strdup(err_message);
	}
}

void	check_if_between_pipes_is_empty(char *parsing_line,
			char *mask, t_syx_check syx)
{
	int	i;
	int	is_only_spaces;

	i = 0;
	is_only_spaces = 1;
	i = ft_strlen(mask) - 1;
	while (i >= 0 && mask[i] != '|')
	{
		if (mask[i] != 'W')
			is_only_spaces = 0;
		i--;
	}
	if (is_only_spaces)
		syntax_set_error(syx, "error aroudn the pipe");
}
