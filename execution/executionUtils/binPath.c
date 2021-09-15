/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binPath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:29:49 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/15 16:06:00 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	freeVars(char **splittedPath)
{
	int		i;

	i = 0;
	while (splittedPath[i])
	{
		free(splittedPath[i]);
		i++;
	}
	free(splittedPath);
}

char	*returnBinPath(char *binPath, int *binFd, char **command)
{
	close(*binFd);
	free(*command);
	return (binPath);
}

char	*getBinPath(char *command, char **splittedPath)
{
	int		i;
	int		binFd;
	char	*binPath;
	char	*tmp_bin;

	i = 0;
	binPath = ft_strdup("");
	while (splittedPath[i])
	{
		free(binPath);
		binPath = ft_strjoin(splittedPath[i], "/");
		tmp_bin = binPath;
		binPath = ft_strjoin(tmp_bin, command);
		free(tmp_bin);
		binFd = open(binPath, O_RDONLY);
		if (binFd > 0)
			return (returnBinPath(binPath, &binFd, &command));
		i++;
	}	
	free(binPath);
	return (command);
}

char	*binPath(char *cmd, t_dlist envl)
{
	char	*binPath;
	char	**splittedPath;

	binPath = NULL;
	splittedPath = ft_split(ft_getenv("PATH", envl), ':');
	if (splittedPath == NULL)
		return (cmd);
	binPath = getBinPath(cmd, splittedPath);
	freeVars(splittedPath);
	return (binPath);
}
