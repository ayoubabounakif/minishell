/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:15:55 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/16 14:02:55 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <math.h>
# include <errno.h>
# include <time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../parser/parser.h"
# include "../heredoc/heredoc.h"

enum	e_MACROS {
	TRUE = 1,
	FALSE = 0,
	READ = 0,
	WRITE = 1,
	UPPERCASE_BUILTINS = 2,
	HEREDOC_DELIM = 0,
	CHILD = 0,
	YES_PIPE = 1
};

/*
** _420sh STRUCTS
*/

typedef struct s_env
{
	char		*key;
	char		*value;
	char		sep;
	int			has_value;
}				t_env;

/*
**	signals
**/
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		sig_handler(int sign_num);

/*
**	execution
*/
void		executeParsedLine(t_dlist parsed_line, t_dlist envl);
void		forkPipes(t_dlist pipeline, t_dlist envl);
int			spawnProc(
				int in, int *pipeFds, t_commands_table command, t_dlist envl);
int			spawnLastProc(
				int in, int *pipeFds, t_commands_table command, t_dlist envl);
void		inputOutputRedirection(t_commands_table command);
int			executeBuiltins(t_commands_table command, t_dlist envl);

/*
**	executionUtils
*/
void		dup2InputOutput(int in, int out);
char		*binPath(char *cmd, t_dlist envl);
int			isBuiltin(char *token);
void		printErrorMessage(char *command, char *messageToPrint);
int			checkExecutable(char *token);
int			checkDirectory(char *token);

/*
**	builtins
**/
int			__cd__(t_commands_table command, t_dlist env_list);
int			__pwd__(t_commands_table command, t_dlist env_list);
int			__echo__( t_commands_table command, t_dlist env_list);
int			__export__(t_commands_table command, t_dlist env_list);
int			__unset__(t_commands_table command, t_dlist env_list);
int			__env__(t_commands_table command, t_dlist env_list);
int			__exit__(t_commands_table command, t_dlist env_list);

/*
**	env
**/
char		**env_list_to_env_array(t_dlist env_list);
char		*find_envv_akey_value(char *key, t_dlist env_list);
t_env		*find_envv_key_node(char *key, t_dlist env_list);

/*
**	env-subroutines
*/
t_env		*env_create(char *key, char *value);
void		env_destroy(void *env_);
void		env_array_destroy(char **env_array);

/*
**	env-getters
*/
char		*ft_getenv(char *name, t_dlist env_list);
t_dlist		get_envs(char **env);
char		*get_key(char *line);
char		*get_value(char *line);

/*
**	expansion
*/
void		expandEnvVarsInParsedData(t_dlist parsed_data_lst, t_dlist env_lst);
void		last_commandCode_expend(t_dlist env_lst);
void		expandNormalTokens(void *data, t_dlist env_lst);
#endif
