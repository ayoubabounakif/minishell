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

char	*binPath(char *cmd, t_dlist envl)
{
	t_env *_420sh_env;
	int bin_fd;
	char *path;
	char *binPath;
	char **split_path;
	int i;

	i = 0;
	binPath = NULL;
	dlist_move_cursor_to_head(envl);
	while (envl->cursor_n != envl->sentinel)
	{
		_420sh_env = envl->cursor_n->value;
		if (strcmp(_420sh_env->key, "PATH") == 0)
			path = _420sh_env->value;
		dlist_move_cursor_to_next(envl);
	}
	split_path = ft_split(path, ':');
	if (split_path == NULL)
	{
		ft_putstr_fd("_420sh: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (NULL);
	}
	while (split_path[i])
	{
		binPath = ft_strjoin(split_path[i], "/");
		binPath = ft_strjoin(binPath, cmd);
		bin_fd = open(binPath, O_RDONLY);
		if (bin_fd > 0)
		{
			close(bin_fd);
			return (binPath);
		}
		i++;
	}
	ft_putstr_fd("_420sh: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	i = 0;
	free(binPath);
	while (split_path[i])
	{
		free(split_path[i]);
		i++;
	}
	free(split_path);
	return (NULL);
}
