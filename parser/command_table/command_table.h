/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:01:06 by khafni            #+#    #+#             */
/*   Updated: 2021/09/10 13:34:13 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H
# include "../../CPCA/generic_parrays/garrptr.h"
# include "../pipelines.h"
# include "../../dlist/dlists.h"
# include "../quotes_proccessing.h"
# include "../env_variables.h"
# include "../syntax_checking.h"

# define REDI_INPUT_FILE 1
# define REDI_OUTPUT_FILE 2
# define REDI_APPEND_FILE 3
# define REDI_HEREDOC_FILE 4

/*
** private struct and methods
*/

typedef struct s_redir_file
{
	char	*file_name;
	char	file_type;
}	*t_redir_file;

t_redir_file		redir_file(char *file_name, char type_of_file);
void				redir_file_destroy(void *rf_);

typedef struct s_commands_table
{
	t_tokens	tokens_unproccessed;	
	t_arrptr	tokens;
	t_arrptr	redir_files;
	char		is_after_p_or_sc;
	char		is_there_a_red_error;
}	*t_commands_table;

int					is_normal_token(t_commands_table cmdt);
int					is_token_a_r_i_file(t_commands_table cmdt);
int					is_token_a_r_o_file(t_commands_table cmdt);
int					is_token_a_r_app_file(t_commands_table cmdt);
int					is_token_a_r_heredoc_file(t_commands_table cmdt);

t_commands_table	cmd_table(t_pipeline pl, t_dlist env_list);
void				cmd_table_fill(t_commands_table cmdt, t_pipeline pl);

void				cmd_table_destroy(void *cmd_tab_);

/*
** public struct and methods
*/

typedef struct s_command
{
	char		**tokens;
	t_arrptr	redir_files;
	char		is_pipe;
	char		is_only_command;
	char		is_after_p_or_sc;
	char		is_there_a_red_error;
}				t_command;

t_command			*command_table(t_commands_table cmd, t_dlist env_list);
void				command_table_destroy(void *cmd_tab_);

#endif