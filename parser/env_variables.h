#ifndef ENV_VARIABLES_H
# define ENV_VARIABLES_H

# include "pipelines.h"
//# include "command_table/command_table.h"
//#include "../includes/minishell.h"


char *rstr_find_and_replace(t_rstr haystack, char *needle, char *new_needle);
char *str_find_and_replace(char *haystack, char *needle, char *new_needle);

char    *print_the_env_var(char *token, char *token_mask, int i);
char    *find_replace_env_vars_in_a_token(char *token, char *token_mask, t_dlist env_list);
//void    expand_env_variables(t_command cmd, t_dlist env_list);
void    expand_env_variables(t_tokens tks, t_dlist env_list);
//void    expand_env_variables_test(t_command *cmd, t_dlist env_list);

# endif