/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:06:22 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/19 15:06:23 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	process(int sign_num)
{
	if (!kill(g_vars.pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", STDOUT);
			g_vars.exit_code = 131;
		}
		else if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', STDOUT);
			g_vars.exit_code = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT);
		g_vars.exit_code = 1;
		ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", STDOUT);
		ft_putstr_fd("\x1B[32m", STDOUT);
		ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", STDOUT);
	}
}

void		sig_handler(int sign_num)
{
	if ((sign_num == SIGINT || sign_num == SIGQUIT) && g_vars.pid != 0)
		process(sign_num);
	else
	{
		if (sign_num == SIGINT)
		{
			// This will be changed with termcaps
			ft_putchar_fd('\n', STDOUT);
			g_vars.exit_code = 1;
			ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", STDOUT);
			ft_putstr_fd("\x1B[32m", STDOUT);
			ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", STDOUT);
		}
		// This will be changed with termcaps
		else if (sign_num == SIGQUIT)
			ft_putstr_fd("\b\b  \b\b", STDOUT);
	}
}
