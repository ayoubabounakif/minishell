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


void	processHeredoc(t_dlist pipeline)
{	
	dlist_move_cursor_to_head(pipeline);	
	while (pipeline->cursor_n != pipeline->sentinel)
	{
		heredoc_for_one_cmd_table(pipeline->cursor_n->value);	
		dlist_move_cursor_to_next(pipeline);
	}
	return ;
}

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
	while (420)
	{
		// line = readline("\033[0;32m420\033[0;36mshell \033[0;32m(*∀*)y─\033[0;37m┛ => \33[0m");	
		line = readline("420shell(*∀*)y─┛ => ");	
		parsed_line = NULL;
		if (line && *line)
		{
			// printf("|%s|", get_mask(line));
			parsed_line = parse_line(line, env_list);
			// check_redir_syntax(line);
			add_history(line);
			if (!parsed_line)
				continue ;	
			processHeredoc(parsed_line);
			executeParsedLine(parsed_line, env_list);
			dlist_destroy(parsed_line);
			free(line);
		}
		else if (!line)
		{
			if (parsed_line)
				dlist_destroy(parsed_line);
			exit(EXIT_FAILURE);
		}	
	}	
	return (EXIT_SUCCESS);
}
