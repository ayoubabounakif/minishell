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
	(void)ac;
	(void)av;

	char		*line = NULL;
	int			n = 1;
	t_dlist 	parsed_line; 
	t_dlist		env_list;
	t_syx_check	sx;		

	sx = syntax_check_create();
	env_list = get_envs(envp);
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);

	while (1)
	{
		line = readline("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m\x1B[32m\x1B[0m\x1B[31m$ \x1B[0m");
		//line = readline("420 shell ::> ");
		if (line && *line)
		{
			//printf("|||||$%p$||||\n", line);
			parsed_line = parse_line(line, env_list);
			add_history(line);
			free(line);
			executeParsedLine(parsed_line, env_list);
			dlist_destroy(parsed_line);
		}
		else if (!line)
		{
			exit(1);
		}
		
	}
	/* line = readline("> ");
	parsed_line = parse_line(line, env_list);
	t_dlist sublst;
	t_redir_file rf;
	t_command *cmd;
	dlist_move_cursor_to_head(parsed_line);
	while (parsed_line->cursor_n != parsed_line->sentinel)
	{
		sublst = parsed_line->cursor_n->value;
		dlist_move_cursor_to_head(sublst);
		while (sublst->cursor_n != sublst->sentinel)
		{
			cmd = sublst->cursor_n->value;
			printf("%s %d\n", ((t_redir_file)arrptr_get(cmd->redir_files, 0))->file_name, ((t_redir_file)arrptr_get(cmd->redir_files, 0))->file_type);
			dlist_move_cursor_to_next(sublst);
		}
		dlist_move_cursor_to_next(parsed_line);
	} */
	return (EXIT_SUCCESS);
}
