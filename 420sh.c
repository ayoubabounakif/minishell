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

int	main(int ac, char **av, char **envp)
{
	char		*line;	
	t_dlist 	parsed_line; 
	t_dlist		env_list;

	line = NULL;
		
	(void)ac;
	(void)av;	
	env_list = get_envs(envp);
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	while (420)
	{
		line = readline("420shell (*∀*)y─┛ => ");
		parsed_line = NULL;
		if (line && *line)
		{
			parsed_line = parse_line(line, env_list);
			add_history(line);
			if (!parsed_line)
			{	
				free(line);
				g_vars.exit_code = 127;	
				continue ;
			}
			processHeredoc(parsed_line);
			executeParsedLine(parsed_line, env_list);
			dlist_destroy(parsed_line);		
			free(line);
		}
		else if (!line)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			if (parsed_line)
				dlist_destroy(parsed_line);
			free(line);	
			exit(EXIT_SUCCESS);
		}
		system("leaks minishell");
	}	
	return (EXIT_SUCCESS);
}
