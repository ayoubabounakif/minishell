/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   420sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:40:22 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/06 12:55:55y khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minishell.h"
# include "dlist/dlists.h"
/* #include "parser/pipelines.h"
# include "parser/redirection_splitting/reder_split.h"
# include "parser/quotes_proccessing.h"
# include "parser/command_table/command_table.h" */
//#include "parser/command_table_generator.h"
#include "parser/syntax_checking.h"

int		main(int ac, char **av, char **envp)
{
	( void)ac;
	(void)av;

	char		*line;
	int			n = 1;
	t_dlist 	parsed_line; 
	t_dlist		env_list;
	t_syx_check	sx;		

	sx = syntax_check_create();
	env_list = get_envs(envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", STDOUT_FILENO);
		ft_putstr_fd("\x1B[32m", STDOUT_FILENO);
		ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", STDOUT_FILENO);
		n = get_next_line(STDIN_FILENO, &line);
		parsed_line = parse_line(line, env_list);
		if (n == 0)
		{
			printf("exit\n");
			break ;
		}
		execute_parsed_line(parsed_line, env_list);
	}
	/* {
	n = get_next_line(STDIN_FILENO, &line);
	parsed_line = parse_line(line, env_list);

	t_dlist sub_list;
	t_command *cmd;

	dlist_move_cursor_to_head(parsed_line);
	while (parsed_line->cursor_n != parsed_line->sentinel)
	{
		sub_list = parsed_line->cursor_n->value;	
		dlist_move_cursor_to_head(sub_list);
		while (sub_list->cursor_n != sub_list->sentinel)
		{
			cmd = sub_list->cursor_n->value;
			for (int i = 0; cmd->tokens[i]; i++)
				printf("\n|%s|\n", cmd->tokens[i]);
			dlist_move_cursor_to_next(sub_list);
		}
		dlist_move_cursor_to_next(parsed_line);
	}
	} */
	return (EXIT_SUCCESS);
}
