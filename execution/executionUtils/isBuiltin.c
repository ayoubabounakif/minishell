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
	static const char *builtins[7] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};
	static const char *uppercaseBuiltins[7] = {
		"ECHO",
		"CD",
		"PWD",
		"EXPORT",
		"UNSET",
		"ENV",
		"EXIT",
	};

	(i) = 0;
	while ((i) < 7)
	{
		if (token)
		{
			if (strcmp(token, uppercaseBuiltins[(i)]) == 0)
				return (UPPERCASE_BUILTINS);
			if (strcmp(token, builtins[(i)]) == 0)
				return (TRUE);
		}
		(i)++;
	}
	return (FALSE);
}
