/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __cd__.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:37:37 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/06 12:37:38 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int __cd__(t_commands_table command, t_dlist env_list)
{
	(void)env_list;
	if (chdir(command->tokens_simpl[1]) == 0)
		return (EXIT_SUCCESS);
	else
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	return (EXIT_SUCCESS);
}
