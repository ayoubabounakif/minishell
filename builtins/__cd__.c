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

int __cd__(char **tokens, t_dlist env_list)
{
	(void)env_list;
	if (tokens[1] == NULL)
		ft_putstr_fd("aksh: expected argument to cd\n", STDERR);
	else if (chdir(tokens[1]) == 0)
		printf("Directory changed to %s\n", tokens[1]);
	else
		ft_exit("An error occurred (errno is set).");
	return (1);
}
