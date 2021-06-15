/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_generator.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 17:01:17 by khafni            #+#    #+#             */
/*   Updated: 2021/06/14 13:30:31 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TABLE_GENERATOR_H
# define COMMAND_TABLE_GENERATOR_H

/* # include "../dlist/dlists.h"
# include "../CPCA/generic_parrays/garrptr.h" */
# include "command_table/command_table.h"
# include "syntax_checking.h"

/*
** all the command tables are listed in a sequential way but
** one can check if a command table is ended by a pipe or semicolon or nothing
** with the is_after_p_or_sc member of every command table
** to get one pipeline a time
*/

t_dlist     cmd_tables(char *parsing_text, t_dlist env_list);
void        cmd_tables_destroy(t_dlist cmd_tables_list);
t_dlist 	cmd_tables_list_(char *parsing_text, t_dlist env_list);
void		cmd_tables_list_destroy_(t_dlist cmds_array);

/*
** public methods
*/

t_dlist		cmd_tables_list(char *parsing_text, t_dlist env_list);
void		cmd_tables_list_destroy_(t_dlist cmds_array);

t_dlist		parse_line(char *parsing_line, t_dlist env_list);

#endif