/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 10:57:59 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/18 10:58:00 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	if (kill(g_vars.pid, sig) == 0)
		ft_putstr_fd("\n", STDOUT);
	else
	{
		ft_putstr_fd("\n\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", STDOUT);
		ft_putstr_fd("\x1B[32m", STDOUT);
		ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", STDOUT);
	}
    return ;
}