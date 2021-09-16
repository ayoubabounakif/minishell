/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_generator2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:46:01 by khafni            #+#    #+#             */
/*   Updated: 2021/09/15 16:24:17 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_space_only(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

void	is_empty_cmd(char *str)
{
	char	*tmp;

	tmp = ft_strtrim(str, " ");
	if (is_cstrs_equal("\"\"", tmp))
		syntax_set_error("command not found");
	free(tmp);
	tmp = ft_strtrim(str, " ");
	if (is_cstrs_equal("''", tmp))
		syntax_set_error("command not found");
	free(tmp);
}

void	parse_line_hack(t_dlist cmd_tbs_lists)
{
	g_vars.exit_code = 258;
	syntax_print_error();
	dlist_destroy(cmd_tbs_lists);
	syntax_destroy();
}

t_dlist	parse_line(char *parsing_line, t_dlist env_list)
{
	t_dlist		cmd_tbs_lists;
	t_syx_check	*syx;

	if (!ft_strlen(parsing_line))
		return (NULL);
	syx = syntax_check_create();
	check_pipes_n_semiclns(parsing_line);
	check_redir_syntax(parsing_line);
	if (is_space_only(parsing_line) || !ft_strlen(parsing_line))
		return (NULL);
	if (syx->is_error)
	{
		g_vars.exit_code = 258;
		syntax_print_error();
		return (NULL);
	}
	parse_line_helper(parsing_line, env_list, &cmd_tbs_lists);
	if (syx->is_error)
	{
		parse_line_hack(cmd_tbs_lists);
		return (NULL);
	}
	syntax_destroy();
	return (cmd_tbs_lists);
}
