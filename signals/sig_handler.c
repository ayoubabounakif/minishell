/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:06:22 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/09 15:49:39 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ext_process(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		ft_putchar_fd('\r', STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	process(int signum)
{
	if (!kill(g_vars.pid, signum))
	{
		if (signum == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
			g_vars.exit_code = 131;
		}
		else if (signum == SIGINT)
		{
			ft_putchar_fd('\n', STDERR_FILENO);
			g_vars.exit_code = 130;
		}
	}
	else
		ext_process(signum);
}

void		sig_handler(int signum)
{
	if ((signum == SIGINT || signum == SIGQUIT) && g_vars.pid != CHILD)
		process(signum);
	else
	{
		if (signum == SIGINT)
		{
			ft_putchar_fd('\n', STDERR_FILENO);
			rl_on_new_line();
			rl_replace_line("", STDIN_FILENO);
			rl_redisplay();
			g_vars.exit_code = 1;
		}
		else if (signum == SIGQUIT)
		{
			ft_putchar_fd('\r', STDERR_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
