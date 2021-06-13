/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:19:42 by khafni            #+#    #+#             */
/*   Updated: 2021/06/13 19:45:57 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_checking.h"

t_syx_check	syntax_check_create(void)
{
	t_syx_check syx;

	syx = malloc(sizeof(struct s_syntax));
	syx->is_error = 0;
	syx->error_message = NULL;
	syx->mask = NULL;
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

void check_pipes(char *parsing_pipeline, t_syx_check syx)
{
	int i;

	i = 0;
	while (syx->mask[i])
	{
		if (i >= 0 && i < (ft_strlen(syx->mask) - 1))
		{
			if (syx->mask[i] == '|' && syx->mask[i + 1] == '|')
				syntax_set_error(syx, "Error\npipes duplicated\n");
		}
		i++;
	}
	if (syx->mask[ft_strlen(syx->mask) - 1] == '|')
		syntax_set_error(syx, "error\npipe error");
		
}

void check_semiclns(char *parsing_pipeline, t_syx_check syx)
{
	int i;

	i = 0;
	while (syx->mask[i])
	{
		if (i >= 0 && i < (ft_strlen(syx->mask) - 1))
		{
			if (syx->mask[i] == ';' && syx->mask[i + 1] == ';')
				syntax_set_error(syx, "Error\nsemicolon symbol duplicated\n");
		}
		i++;
	}
	if (syx->mask[ft_strlen(syx->mask) - 1] == ';')
		syntax_set_error(syx, "error\nsemicolon error");
}
void check_pipes_n_semiclns(char *parsing_pipeline, t_syx_check syx)
{
	check_pipes(parsing_pipeline, syx);
	check_semiclns(parsing_pipeline, syx);
}

void check_redirections(char *parsing_pipeline, t_syx_check syx);

void		parse_syntax(char *parsing_pipeline)
{
	t_syx_check syx;

	syx = syntax_check_create();
	syx->mask = get_mask(parsing_pipeline);
	check_pipes_n_semiclns(parsing_pipeline, syx);
	if (syx->is_error)
	{
		printf("%s", syx->error_message);
		syntax_destroy(syx);	
	}
	//printf("%s\n", syx->mask);
	syntax_destroy(syx);
}