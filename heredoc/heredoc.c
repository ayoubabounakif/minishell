/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:45:21 by khafni            #+#    #+#             */
/*   Updated: 2021/09/07 11:42:30 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

unsigned int generate_random_value(void)
{
	int			fd;	
	unsigned	randval;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &randval, sizeof(randval));
	close(fd);
	return (randval);
}

t_arrptr	get_array_of_heredoc_files(t_commands_table cmd)
{
	t_arrptr her_arr;
	t_redir_file rf;
	int i;

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

int		heredoc_repl_save(char *file)
{
	int		fd;
	char	*line;
	char	*tmp_str;
	
	tmp_str = ft_itoa(generate_random_value());
	fd = open(tmp_str, O_RDWR, S_IRWXU);
	while (1)
	{	
		line = readline("heredoc> ");
		if (!ft_strncmp(line, file, ft_strlen(file)))
		{
			free(line);
			free(tmp_str);
			close(fd);
			return (fd);
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);		
	}	
}

void	heredoc_repl_non_save(char *file)
{	
	char	*line;
	
	while (1)
	{	
		line = readline("heredoc> ");		
		if (!ft_strncmp(line, file, ft_strlen(file)))
		{
			free(line);
			return ;
		}
		free(line);	
	}
}

int     heredoc_for_one_cmd_table(t_commands_table cmd)
{
	t_arrptr 	hdoc_file_names;
	int			i;
	char		*str;
	int			fd;

	hdoc_file_names = get_array_of_heredoc_files(cmd);	
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
		fd = heredoc_repl_save(str);
	}
	else
		fd = -42;
	arrptr_destroy(hdoc_file_names);
	return (fd);
}
