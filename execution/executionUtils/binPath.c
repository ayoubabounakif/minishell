/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binPath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:29:49 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/27 17:30:10 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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

	i = 0;
	while (splittedPath[i])
	{
		binPath = ft_strjoin(splittedPath[i], "/");
		binPath = ft_strjoin(binPath, command);
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

static char	*findPathValue(t_dlist envl)
{
	t_env	*_420sh_env;
	char	*path;

	dlist_move_cursor_to_head(envl);
	while (envl->cursor_n != envl->sentinel)
	{
		_420sh_env = envl->cursor_n->value;
		if (strcmp(_420sh_env->key, "PATH") == 0)
		{
			path = _420sh_env->value;
			return (path);
		}
		dlist_move_cursor_to_next(envl);
	}
	return (path);
}

char	*binPath(char *cmd, t_dlist envl)
{
	int		bin_fd;
	char	*binPath;
	char	**splittedPath;
	int		i;

	binPath = NULL;
	splittedPath = ft_split(findPathValue(envl), ':');
	if (splittedPath == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_vars.exit_code = 127;
		return (NULL);
	}
	binPath = getBinPath(cmd, splittedPath);
	if (binPath == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_vars.exit_code = 127;
		freeVars(splittedPath, binPath);
	}
	else
		return (binPath);
	return (NULL);
}
