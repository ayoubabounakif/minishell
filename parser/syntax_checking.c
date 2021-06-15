/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:19:42 by khafni            #+#    #+#             */
/*   Updated: 2021/06/15 13:03:29 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_checking.h"

t_syx_check	syntax_check_create(void)
{
	static t_syx_check syx;

	syx = malloc(sizeof(struct s_syntax));
	syx->is_error = 0;
	syx->error_message = NULL;
	return (syx);
}
void		syntax_destroy(t_syx_check sx)
{
	if (sx->error_message)
		free(sx->error_message);	
	free (sx);
}

void		syntax_set_error(t_syx_check sx, char *err_message)
{
	if (!sx->is_error)
	{
		sx->is_error = 1;
		sx->error_message = ft_strdup(err_message);
	}
}