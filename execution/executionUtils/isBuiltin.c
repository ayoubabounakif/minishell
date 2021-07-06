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
	static const char *builtins[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};
	static const char *uppercaseBuiltins[] = {
		"ECHO",
		"CD",
		"PWD",
		"EXPORT",
		"UNSET",
		"ENV",
		"EXIT",
	};

	i = 0;
	while (i < 7)
	{
		if (strcmp(token, builtins[i]) == 0)
			return (TRUE);
		if (strcmp(token, uppercaseBuiltins[i]) == 0)
			return (UPPERCASE_BUILTINS);
		i++;
	}
	return (FALSE);
}
