/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkExecutable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:53:33 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/15 16:53:36 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkExecutable(char *token)
{
	int	fd;

	fd = open(token, O_RDONLY);
	if (fd < 0)
		return (0);
	return (1);
}
