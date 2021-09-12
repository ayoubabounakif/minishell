/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binPath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:29:49 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/11 14:11:05 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	freeVars(char **splittedPath, char *binPath)
{
	int		i;

	i = 0;
	free(binPath);
	while (splittedPath[i])
	{
		free(splittedPath[i]);
		i++;
	}
	free(splittedPath);
}

static char	*getBinPath(char *command, char **splittedPath)
{
	int		i;
	int		binFd;
	char	*binPath;
	char	*tmp_bin;

	i = 0;
	while (splittedPath[i])
	{
		binPath = ft_strjoin(splittedPath[i], "/");
		tmp_bin = binPath;
		binPath = ft_strjoin(binPath, command);
		free(tmp_bin);
		binFd = open(binPath, O_RDONLY);
		if (binFd > 0)
		{
			close(binFd);
			return (binPath);
		}
		i++;
	}
	return (NULL);
}

char	*binPath(char *cmd, t_dlist envl)
{
	char	*binPath;
	char	**splittedPath;

	binPath = NULL;
	splittedPath = ft_split(ft_getenv("PATH", envl), ':');
	if (splittedPath == NULL)
		return (NULL);
	binPath = getBinPath(cmd, splittedPath);
	if (binPath == NULL)
		freeVars(splittedPath, binPath);
	else
		return (binPath);
	return (NULL);
}
