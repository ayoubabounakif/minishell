/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkDirectory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:06:37 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/15 17:06:54 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkDirectory(char *token)
{
	DIR	*dir;

	dir = opendir(token);
	if (dir == NULL)
		return (0);
	return (1);
}
