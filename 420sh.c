/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   420sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:40:22 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/16 14:18:49 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	endLoop(t_dlist *parsed_line, char **line)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (*parsed_line)
		dlist_destroy(*parsed_line);
	syntax_destroy();
	free(*line);
	if (g_vars.exit_code == 1)
		exit(g_vars.exit_code);
	else
		exit(EXIT_SUCCESS);
}

void	destroyWuss(t_dlist *parsed_line, char **line)
{
	dlist_destroy(*parsed_line);
	syntax_destroy();
	free(*line);
}

void	mariPrompt(t_dlist *parsed_line, char **line, t_dlist *env_list)
{
	while (420)
	{
		*line = readline("\033[0;36m420shell (*∀*)y─┛ => \033[0m");
		*parsed_line = NULL;
		if (*line)
		{	
			*parsed_line = parse_line(*line, *env_list);
			add_history(*line);
			if (!*parsed_line)
			{	
				free(*line);
				syntax_destroy();
				continue ;
			}
			processHeredoc(*parsed_line);
			executeParsedLine(*parsed_line, *env_list);
			destroyWuss(parsed_line, line);
		}
		else if (!*line)
			endLoop(parsed_line, line);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_dlist	parsed_line;
	t_dlist	env_list;

	line = NULL;
	(void)ac;
	(void)av;
	env_list = get_envs(envp);
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	mariPrompt(&parsed_line, &line, &env_list);
	return (EXIT_SUCCESS);
}
