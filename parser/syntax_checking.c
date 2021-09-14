/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:42:49 by khafni            #+#    #+#             */
/*   Updated: 2021/09/14 18:42:51 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_syx_check	*syntax_check_create(void)
{
	static t_syx_check	syx;
	static int			init = 0;

	if (init == 0)
	{
		syx.is_error = 0;
		syx.error_message = NULL;
		init = 1;
	}
	return (&syx);
}

void	syntax_destroy(void)
{
	t_syx_check	*sx;

	sx = syntax_check_create();
	if (sx->is_error)
		free(sx->error_message);
	sx->error_message = NULL;
	sx->is_error = 0;
}

void	syntax_set_error(char *err_message)
{
	t_syx_check	*sx;

	sx = syntax_check_create();
	if (!sx->is_error)
	{
		sx->is_error = 1;
		sx->error_message = ft_strdup(err_message);
	}
	else
	{
		free(sx->error_message);
		sx->error_message = ft_strdup(err_message);
	}
}

void	syntax_print_error(void)
{
	t_syx_check	*sx;

	sx = syntax_check_create();
	if (sx->is_error)
	{
		printf("%s\n", sx->error_message);
		sx->is_error = 0;
		free(sx->error_message);
	}
}

void	check_if_between_pipes_is_empty(char *mask)
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
		syntax_set_error("error around the pipe");
}
