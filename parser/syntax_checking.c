/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:19:42 by khafni            #+#    #+#             */
/*   Updated: 2021/07/01 15:02:01 by khafni           ###   ########.fr       */
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

void    check_pipes_n_semiclns(char *parsing_line, t_syx_check syx)
{
	int i;
	int is_pipe;
	int is_sc;

	i = 0;
	is_pipe = 0;
	is_sc = 0;
	while (parsing_line[i])
	{
		if ((is_pipe || is_sc) && (parsing_line[i] != '|' && parsing_line[i] != ';'))
		{
			is_pipe = 0;
			is_sc = 0;
		}
		if (is_pipe && parsing_line[i] == '|') 
			syntax_set_error(syx, "error aroudn the pipe"); 
		else if (is_sc && parsing_line[i] == ';') 
			syntax_set_error(syx, "error aroudn the semicolon"); 
		else if (!is_pipe && parsing_line[i] == '|') 
			is_pipe = 1; 
		else if (!is_sc && parsing_line[i] == ';') 
			is_sc = 1; 
		if (ft_strlen(parsing_line) >= 1 && (parsing_line[ft_strlen(parsing_line) - 1] == '|'
		|| parsing_line[ft_strlen(parsing_line) - 1] == ';'))
			syntax_set_error(syx, "error around the pipe or semicolon");
		i++;
	}
}
