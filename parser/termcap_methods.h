#ifndef TERMCAP_METHODS_H
# define TERMCAP_METHODS_H

# define KEY_UP_U -73
# define KEY_UP_D -72
# define KEY_REMOVE 127

struct s_history_node
{
	char *str_1;
	char *str_2;
};

typedef struct s_history_node *t_history_node;
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../dlist/dlists.h"
int init_term(void);



#endif