/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:45:21 by khafni            #+#    #+#             */
/*   Updated: 2021/09/06 19:35:39 by khafni           ###   ########.fr       */
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

int		heredoc_repl_save(char *file, char is_safe_output)
{
	int		fd;
	char	*line;
	
	fd = open(file, O)
	while (1)
	{	
		line = readline("heredoc> ");	
		if (ft_strncmp(line, file, ft_strlen(file)))
		{
			free(line);
			return (-420);
		}
		free(line);		
	}
}

int		heredoc_repl_non_save(char *file, char is_safe_output)
{	
	char	*line;
	
	while (1)
	{	
		line = readline("heredoc> ");	
		if (ft_strncmp(line, file, ft_strlen(file)))
		{
			free(line);
			return (-420);
		}
		free(line);		
	}
}

int		heredoc_repls_before_last_file(t_arrptr hdoc_file_names)
{

}

int     heredoc_for_one_cmd_table(t_commands_table cmd)
{
	t_arrptr 	hdoc_file_names;
	int			i;

	hdoc_file_names = get_array_of_heredoc_files(cmd);
	i = 0;
	while (i < hdoc_file_names->len - 1 && (hdoc_file_names->len > 1))
	{
		heredoc_repls_before_last_file(hdoc_file_names);
		i++;
	}	
	arrptr_destroy(hdoc_file_names);
}
