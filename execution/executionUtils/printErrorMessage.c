/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printErrorMessage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:19:21 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/29 17:19:41 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printErrorMessage(char *command, char *messageToPrint)
{
	ft_putstr_fd("_420sh: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(messageToPrint, STDERR_FILENO);
	ft_putstr_fd("<---> ERRNO: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}
