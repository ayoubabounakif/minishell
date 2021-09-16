/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 07:25:10 by khafni            #+#    #+#             */
/*   Updated: 2021/09/16 10:18:54 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "../CPCA/generic_parrays/garrptr.h"
# include "../dlist/dlists.h"
# include "../dlist/dlist_norm_hack.h"
# include <fcntl.h>
# include <errno.h>

# define IS_AFTER_PIPE 1
# define IS_AFTER_SEMICOLON 2
# define NO_PIPE_OR_SEMICOLON 3

typedef struct s_vars
{
	pid_t		pid;
	int			exit_code;
	int			noneOfUrBusiness;
}				t_vars;

t_vars			g_vars;
/*
** norm hacking structures "the norm sucks you can't change my mind"
*/

typedef struct s_find_replace_env
{
	char	*token;
	char	*token_mask;
	int		i;
	t_dlist	env_list;
	char	*is_key_found;
	char	*r_str;
	char	*tmp;
}	t_find_replace_env;

typedef struct s_split_token_w_red
{
	char		*token;
	t_rstr		rs;	
	t_arrptr	arr;
	int			i;
	char		*mask;
}	t_split_token_w_red;

typedef struct s_raqfos
{
	char	*mask;
	int		sq_state;
	int		dq_state;
	int		i;
	t_rstr	rs;
	char	*a_token;
	char	**r_str;
	int		conti;
}	t_raqfos;

typedef struct s_ftc
{
	t_arrptr	arr_r;
	t_rstr		rs;
	int			i;
	char		*mask;
	char		*str;
	t_arrptr	arr;
}	t_ftc;

typedef struct s_ent
{
	void				*cmd;
	int					i;
	char				*tmp_str;
	char				*mask;
	t_dlist				env_lst;
}	t_ent;
/*
** 
** +-+-+-+-+ +-+-+-+-+-+-+
** |m|a|s|k| |m|o|d|u|l|e|
** +-+-+-+-+ +-+-+-+-+-+-+
*/

/*
** state represents where we're exactly on the command
*/

typedef struct s_state
{
	char	skip;
	char	inside_squote;
	char	inside_dquote;
	char	inside_dquotes_sk;	
	char	env_variable;
	char	env_variable_dq;
}				t_state;

void				init_states(t_state *state);
char				get_mask_char_inside_dq(t_state *state, char *s, int i);
char				get_mask_character(t_state *state, char *s, int i);
char				get_mask_character_helper_last(char c);
char				get_mask_character_helper(t_state *state, char *s, int i);
char				get_mask_character_helper3(t_state *state, char *s, int i);
char				get_mask_c_helper(t_state *state, char *s, int i);
char				*get_mask(char *s);
void				destroy_mask(char **mask_);
t_arrptr			split_using_mask(char *str, char *str_mask, char del);

/*
** +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+
** |p|i|p|e|l|i|n|e| |m|o|d|u|l|e|
** +-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+
*/

/*
** A pipeline is a sequence of one or more commands separated
** by the control operator ‘|’
*/

# define IS_AFTER_PIPE 1
# define IS_AFTER_SEMICOLON 2
# define NO_PIPE_OR_SEMICOLON 3

/*
** after every elementry line we shall know if it's
** followed by a pipe or a semicolon
*/

/*
** the tracked lines will contain the lines + an element that
** states if they're followed by a pipe or ;
*/

typedef struct s_pipeline
{
	char	*cmd_line;
	char	*cmd_line_m;
	char	is_after_p_or_sc;
}	*t_pipeline;

t_pipeline			pipeline(char *cmd_line, char *cmd_line_m,
						char is_after_p_or_sc);
void				pipeline_destroy(void *pl);

t_arrptr			get_pipelines(char *str);

/*
** +-+-+-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+
** |r|e|d|i|r|e|c|t|i|o|n| |s|p|l|i|t|t|i|n|g| |m|o|d|u|l|e|
** +-+-+-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+
*/

/*
** here i just try to split tokens that comes in this format
** word + redir sign, redir sign + word or word
** or any words redir signs combination for parsing
** purposes
*/

/*
** is a token composed of a words and rederection signs
*/
int					is_red_cmd_non_split(char *token_, char *mask);

/*
**	divide a string that contains a 
**	cmd and redirections/appnds or redirections/appnds
**	with the files names into tokens
*/
t_arrptr			split_token_w_red(char *token);

/*
** remplace an individual node in the tokens linked list with
** an array of tokens
*/
void				remplace_cursor_node_with_array(t_dlist l, t_arrptr arr);

/*
** takes the splitted tokens and split them again with respect
** to rederection
*/
void				tokens_split_w_red(t_dlist tokens);

/*
** +-+-+-+-+-+-+ +-+-+-+-+-+-+
** |t|o|k|e|n|s| |m|o|d|u|l|e|
** +-+-+-+-+-+-+ +-+-+-+-+-+-+
*/

typedef struct s_tokens
{
	t_dlist	tokens;
	t_dlist	tokens_masks;
}	*t_tokens;

t_tokens			tokens(t_pipeline pl);
void				tokens_destroy(t_tokens tks);

char				*remove_quotes_from_string(char *a_token);
void				process_tokens_from_quotes(t_tokens tks);

/*
**  __ _  ___  ________ ___ _   _
** (( \\\//||\ ||| || |// \\\\ //
**  \\  )/ ||\\||  ||  ||=|| )X(
** \_))//  || \||  ||  || ||// \\
**   _____  __ ____ _____ ______  __  ___
**  //  ||  ||||   //  || //||||\ || // \\
** ((   ||==||||==((   ||<< ||||\\||(( ___
**  \\__||  ||||___\\__|| \\|||| \|| \\_||
*/

typedef struct s_syntax
{	
	char	is_error;
	char	*error_message;
}	t_syx_check;

t_syx_check			*syntax_check_create(void);
void				syntax_destroy(void);
void				check_redir_syntax(char *parsing_line);
void				check_if_between_pipes_is_empty(char *mask);
void				check_pipes_n_semiclns(char *parsing_pipeline);
void				is_empty_cmd(char *str);
void				preparse_syntax(char *parsing_pipeline);
void				syntax_print_error(void);
void				syntax_set_error(char *error_message);

char				*rstr_find_and_replace(t_rstr haystack, char *needle,
						char *new_needle, char *mask);
char				*str_find_and_replace(char *haystack, char *needle,
						char *new_needle);
char				*find_envv_akey_value(char *key, t_dlist env_list);

char				*print_the_env_var(char *token, char *token_mask, int i);
char				*find_replace_env_vars_in_a_token(char *token,
						t_dlist env_list);
void				expand_env_variables(t_tokens tks, t_dlist env_list);
void				firstTokenExpander(t_dlist parsed_data_lst);

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
	t_tokens		tokens_unproccessed;		
	t_arrptr		tokens;
	char			**tokens_simpl;
	t_arrptr		redir_files;
	char			is_after_p_or_sc;
	char			is_there_a_red_error;
	char			*bin_path_garbage;
	void			**v;
	t_arrptr		ar;
}	*t_commands_table;

int					is_normal_token(t_commands_table cmdt);
int					is_token_a_r_i_file(t_commands_table cmdt);
int					is_token_a_r_o_file(t_commands_table cmdt);
int					is_token_a_r_app_file(t_commands_table cmdt);
int					is_token_a_r_heredoc_file(t_commands_table cmdt);

t_commands_table	cmd_table(t_pipeline pl);
void				cmd_table_fill(t_commands_table cmdt);

/*
**  handle when a command and a redirection symbol are sticked together
** in one word by splitting them & also splits rederection signs and their files
** if they're stuck together
*/

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

typedef struct s_cmd_tables_list
{
	t_dlist		tmp_list_of_command_tables_non_splitted;
	t_dlist		list_of_command_tables_lists;
	t_dlist		a_command_table_list;
	t_command	*cmd_tab;
	int			is_it_time_for_a_new_list;
	int			is_it_end_of_list;
	char		*parsing_text;
	t_dlist		env_list;
}	t_cmd_tables_list;

t_command			*command_table(t_commands_table cmd);
void				command_table_destroy(void *cmd_tab_);

/*
** all the command tables are listed in a sequential way but
** one can check if a command table is ended by a pipe or semicolon or nothing
** with the is_after_p_or_sc member of every command table
** to get one pipeline a time
*/

int					check_if_rd_got_afile(t_commands_table cmdt);
t_dlist				cmd_tables(char *parsing_text);
void				cmd_tables_destroy(t_dlist cmd_tables_list);
t_dlist				cmd_tables_list_(char *parsing_text);
void				cmd_tables_list_destroy_(t_dlist cmds_array);

/*
** public methods
*/

t_dlist				cmd_tables_list(char *parsing_text);
void				cmd_tables_list_destroy_(t_dlist cmds_array);

t_dlist				parse_line(char *parsing_line, t_dlist env_list);
void				expandEnvVarsInParsedData(t_dlist parsed_data_lst,
						t_dlist env_lst);
char				*remove_quotes_from_stringImproved(char *a_token,
						char type_of_quotes);
void				remove_quotes(t_dlist parsed_line);
void				firstTokenExpander(t_dlist pDataL);
void				parse_line_helper(char *parsing_line, t_dlist env_list,
						t_dlist *cmd_tbs_lists);
t_arrptr			first_token_changer(t_arrptr arr);
#endif
