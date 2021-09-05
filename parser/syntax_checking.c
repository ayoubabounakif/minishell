/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:19:42 by khafni            #+#    #+#             */
/*   Updated: 2021/09/05 16:38:57 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_syx_check	syntax_check_create(void)
{
	static t_syx_check syx = NULL;

	if (syx == NULL)
	{
		syx = malloc(sizeof(struct s_syntax));
		syx->is_error = 0;
		syx->error_message = NULL;
	}
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


/* int		check_pipes_syntax_at_first(char *parsing_line)
{
	int	i;
	int	is_pipe;

	i = 0;
	is_pipe = 0;
	if (parsing_line[0] == '|')
		is_pipe = 1;	
	while (parsing_line[i])
	{
		if ()	
		i++;
	}
} */

void    check_pipes_n_semiclns(char *parsing_line, t_syx_check syx)
{
	int i;
	int is_pipe;
	
	i = 0;
	is_pipe = 0;
	if (parsing_line[0] == '|')
		syntax_set_error(syx, "parse error around the pipe");
	while (parsing_line[i])
	{
		if ((is_pipe) && (parsing_line[i] != '|'))
			is_pipe = 0;		
		if (is_pipe && parsing_line[i] == '|') 
			syntax_set_error(syx, "error aroudn the pipe"); 	 
		else if (!is_pipe && parsing_line[i] == '|') 
			is_pipe = 1; 	
		if (ft_strlen(parsing_line) >= 1 && (parsing_line[ft_strlen(parsing_line) - 1] == '|'))
			syntax_set_error(syx, "error around the pipe or semicolon");
		i++;
	}
}
