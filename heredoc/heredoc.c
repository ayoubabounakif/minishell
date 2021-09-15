/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:45:21 by khafni            #+#    #+#             */
/*   Updated: 2021/09/14 12:00:40 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

t_arrptr	get_array_of_heredoc_files(t_commands_table cmd)
{
	t_arrptr		her_arr;
	t_redir_file	rf;
	int				i;

	i = 0;
	her_arr = empty_arrptr_create(free);
	while (i < cmd->redir_files->len)
	{
		rf = arrptr_get(cmd->redir_files, i);
		if (rf->file_type == REDI_HEREDOC_FILE)
			arrptr_add(her_arr, ft_strdup(rf->file_name));
		i++;
	}
	return (her_arr);
}

char	*heredoc_repl_save(char *file)
{
	int		fd;
	char	*line;
	char	*random_string;

	random_string = generate_random_value();
	fd = open(random_string, O_CREAT | O_RDWR, S_IRWXU);
	while (420)
	{	
		line = readline("> ");
		if (!line || !ft_strncmp(line, file, ft_strlen(file)))
		{
			if (line)
				free(line);
			close(fd);
			return (random_string);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	free (random_string);
	close(fd);
	return (NULL);
}

void	heredoc_repl_non_save(char *file)
{	
	char	*line;

	while (420)
	{	
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, file, ft_strlen(file)))
		{
			free(line);
			return ;
		}
		free(line);
	}
	free(line);
}

void
	turn_last_heredoc_delName_into_filename(
		t_commands_table cmd, char *file_name)
{
	int				i;
	t_redir_file	rf;

	i = cmd->redir_files->len - 1;
	while (i >= 0)
	{
		rf = arrptr_get(cmd->redir_files, i);
		if (rf->file_type == REDI_HEREDOC_FILE)
		{
			free(rf->file_name);
			rf->file_name = ft_strdup(file_name);
			rf->file_type = REDI_INPUT_FILE;
		}
		i--;
	}	
}

void	heredoc_for_one_cmd_table(t_commands_table cmd)
{
	t_arrptr	hdoc_file_names;
	int			i;
	char		*str;
	char		*ret_file_name;

	hdoc_file_names = get_array_of_heredoc_files(cmd);
	ret_file_name = NULL;
	i = 0;
	str = arrptr_get(hdoc_file_names, i);
	while (i < hdoc_file_names->len - 1)
	{
		str = arrptr_get(hdoc_file_names, i);
		heredoc_repl_non_save(str);
		i++;
	}
	if (hdoc_file_names->len >= 1)
	{
		str = arrptr_get(hdoc_file_names, i);
		ret_file_name = heredoc_repl_save(str);
		turn_last_heredoc_delName_into_filename(cmd, ret_file_name);
		free(ret_file_name);
	}
	arrptr_destroy(hdoc_file_names);
}
