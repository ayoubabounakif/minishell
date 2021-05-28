#ifndef ENV_VARIABLES_H
# define ENV_VARIABLES_H

# include "pipelines.h"

t_rstr rstr_find_and_replace(t_rstr haystack, char *needle, char *new_needle);
char    *print_the_env_var(char *token, char *token_mask, int i);
void    find_env_vars_in_a_token(char *token, char *token_mask);
void    print_the_env_variables(t_tokens tks);

# endif