/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigquit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 10:58:05 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/18 10:58:06 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigquit(int sig)
{
    (void)sig;
	if (kill(g_vars.pid, sig) == 0)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
    return ;
}