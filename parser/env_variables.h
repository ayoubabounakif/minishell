#ifndef ENV_VARIABLES_H
# define ENV_VARIABLES_H

# include "pipelines.h"

char *rstr_find_and_replace(t_rstr haystack, char *needle, char *new_needle);
char *str_find_and_replace(char *haystack, char *needle, char *new_needle);

char    *print_the_env_var(char *token, char *token_mask, int i);
char    *find_env_vars_in_a_token(char *token, char *token_mask);
void    expand_env_variables(t_tokens tks);

# endif