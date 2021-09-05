/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:19:42 by khafni            #+#    #+#             */
/*   Updated: 2021/09/05 18:50:55 by khafni           ###   ########.fr       */
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
/* int		go_to_next_pipe(char *parsing_line, char *mask)
{

}
 */

void	check_if_between_pipes_is_empty(char *parsing_line, char *mask, t_syx_check syx)
{
	int i;
	int is_only_spaces;

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

void	check_if_after_last_pipe(char *parsing_line, char *mask, t_syx_check syx)
{
	int i;
	int is_pipe;

	i = 0;
	is_pipe = 0;
	while (mask[i])
	{
		if ((is_pipe) && (mask[i] != '|') && mask[i] != 'W')
			is_pipe = 0;
		if (is_pipe && mask[i] == '|')
			syntax_set_error(syx, "error around the pipe");
		else if (!is_pipe && mask[i] == '|') 
			is_pipe = 1;
			i++;
	}
}
void    check_pipes_n_semiclns(char *parsing_line, t_syx_check syx)
{
	int i;
	int is_pipe;
	char	*mask;
	
	mask = get_mask(parsing_line);
	i = 0;
	is_pipe = 0;
	check_if_between_pipes_is_empty(parsing_line, mask, syx);
	check_if_after_last_pipe(parsing_line, mask, syx);
	if (mask[0] == '|')
		syntax_set_error(syx, "parse error around the pipe");
	while (mask[i])
	{
		if ((is_pipe) && (mask[i] != '|'))
			is_pipe = 0;		
		if (is_pipe && mask[i] == '|') 
			syntax_set_error(syx, "error around the pipe"); 	 
		else if (!is_pipe && mask[i] == '|') 
			is_pipe = 1; 	
		if (ft_strlen(parsing_line) >= 1 && (mask[ft_strlen(parsing_line) - 1] == '|'))
			syntax_set_error(syx, "error around the pipe or semicolon");
		i++;
	}
	free(mask);
}
