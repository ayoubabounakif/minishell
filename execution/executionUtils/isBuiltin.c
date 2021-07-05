/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isBuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 18:03:54 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/27 18:04:28 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	isBuiltin(char *token)
{
	int		i;
	const char *builtin_str[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};

	i = 0;
	while (i < 7)
	{
		if (strcmp(token, builtin_str[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
