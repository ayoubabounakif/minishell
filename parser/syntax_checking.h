#ifndef SYNTAX_CHECKER
# define SYNTAX_CHECKER
# include <stdio.h>
# include <stdlib.h>
# include "mask.h"
# include "../libft/libft.h"

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


typedef struct s_syntax *t_syx_check;

struct s_syntax
{
	char *mask;
	char is_error;
	char *error_message;
};

t_syx_check	syntax_check_create(void);
void		syntax_destroy(t_syx_check sx);
void check_pipes_n_semiclns(char *parsing_pipeline, t_syx_check syx);
void		parse_syntax(char *parsing_pipeline);
void		syntax_set_error(t_syx_check sx, char *error_message);
#endif