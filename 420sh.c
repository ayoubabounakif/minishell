/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   420sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:40:22 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/29 17:48:29 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minishell.h"
//# include "dlist/dlists.h"
/* #include "parser/pipelines.h"
# include "parser/redirection_splitting/reder_split.h"
# include "parser/quotes_proccessing.h"
# include "parser/command_table/command_table.h" */
//#include "parser/command_table_generator.h"

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char		*line;
	int			n = 1;
	t_dlist 	parsed_line; 
	t_dlist		env_list;

	env_list = get_envs(envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", STDOUT_FILENO);
		ft_putstr_fd("\x1B[32m", STDOUT_FILENO);
		ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", STDOUT_FILENO);
		n = get_next_line(STDIN_FILENO, &line);
		parsed_line = cmd_tables_list(line, env_list);
		if (n == 0)
		{
			printf("exit\n");
			break ;
		}
		execute_parsed_line(parsed_line, env_list);
	} 

	//printf("%s", get_value())
	//char *s = "ls -l $BIGVAR $donc dddd";
	//printf("%s\n", str_find_and_replace(s, "$donc", "potato"));
	//printf("%s\n", rstr_find_and_replace(cstr_to_rstr(s), "$donc", "potato"));
	//printf("%s\n", find_env_vars_in_a_token(s, get_mask(s)));
	/* is_red_cmd_non_split(">4");	
	t_pipeline pl = pipeline("ls -l", get_mask("ls -l"), NO_PIPE_OR_SEMICOLON);
	remove_quotes_from_string("\"wow\"");
	t_commands_table  cmd = cmd_table(pl, envp);
	/* t_dlist dl = cmd_tables_list("ls -o"); */
	return (EXIT_SUCCESS);
}
