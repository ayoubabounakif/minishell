/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:06:22 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/09 07:34:00 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	process(int sign_num)
{
	if (!kill(g_vars.pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
			g_vars.exit_code = 130;
		}
		else if (sign_num == SIGINT)
		{
			printf("dude\n");
			ft_putchar_fd('\n', STDOUT_FILENO);
			rl_on_new_line();
			// rl_replace_line("fuck", 0);
			rl_redisplay();
			g_vars.exit_code = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_vars.exit_code = 1;
		//ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", STDOUT_FILENO);
		//ft_putstr_fd("\x1B[32m", STDOUT_FILENO);
		//ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", STDOUT_FILENO);
	}
}

// void		sig_handler(int sign_num)
// {
// 	if ((sign_num == SIGINT || sign_num == SIGQUIT) && g_vars.pid != CHILD_PROCESS)
// 		process(sign_num);
// 	else
// 	{
// 		if (sign_num == SIGINT)
// 		{
// 			// This will be changed with termcaps
// 			ft_putchar_fd('\n', STDOUT_FILENO);
// 			g_vars.exit_code = 1;
// 			ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", STDOUT_FILENO);
// 			ft_putstr_fd("\x1B[32m", STDOUT_FILENO);
// 			ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", STDOUT_FILENO);
// 		}
// 		// This will be changed with termcaps
// 		else if (sign_num == SIGQUIT)
// 			ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
// 	}
//}

void	sig_handler(int sign_num)
{
	if (sign_num == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		rl_on_new_line();
		rl_replace_line("", 1); 
		rl_redisplay();
	}
	else if (sign_num == SIGQUIT)
	{
		ft_putchar_fd('\r', 1);

		rl_on_new_line();
		rl_redisplay();
	}
}