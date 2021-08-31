/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __cd__.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:37:37 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/06 12:37:38 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* chdir will change the current directory of your program, probably a command shell you are trying to implement.
Absolute and relative paths such as /, .., subdir pose no problem and can be passed directly to the chdir system call.
- is a special argument for the cd command: cd - means to go back to the previous current directory. To implement this functionality,
you need to keep track of the last directory cd changed to. Use the getcwd() function for that before calling chdir and if successful,
keep this previous directory in a global array.
~ is another special thing: it should be expanded to the home directory
(the value of the HOME environment variable) before dispatching to the command handler,
so one can type cd ~, or just cd to change to the home directory but cd "~" to change to a directory named "~". ~ should expand to $(HOME),
either as a stand alone string or as the initial portion of a path: ~/bin. Note that ~name should expand to the home directory of the user name.
 */

#include "../includes/minishell.h"

# define MAX_PATH 32

char lastdir[MAX_PATH];  // initialized to zero

int __cd__(t_commands_table command, t_dlist env_list)
{
	char	*arg = command->tokens_simpl[1];
    char	curdir[MAX_PATH];
    char	path[MAX_PATH];
	char	lastdir[MAX_PATH];

    if (getcwd(curdir, sizeof curdir)) {
        /* current directory might be unreachable: not an error */
        *curdir = '\0';
    }
    if (arg == NULL) {
        arg = getenv("HOME");
    }
    if (!strcmp(arg, "-")) {
        if (*lastdir == '\0') {
            fprintf(stderr, "no previous directory\n");
        	return (EXIT_FAILURE);
        }
        arg = lastdir;
    } else {
        /* this should be done on all words during the parse phase */
        if (*arg == '~') {
            if (arg[1] == '/' || arg[1] == '\0') {
                snprintf(path, sizeof path, "%s%s", getenv("HOME"), arg + 1);
                arg = path;
            } else {
                /* ~name should expand to the home directory of user with login `name` 
                   this can be implemented with getpwent() */
                fprintf(stderr, "syntax not supported: %s\n", arg);
                return (EXIT_FAILURE);
            }
        }
    }
    if (chdir(arg))
	{
        fprintf(stderr, "chdir: %s: %s\n", strerror(errno), path);
        return (EXIT_FAILURE);
    }
    strcpy(lastdir, curdir);
    return (EXIT_SUCCESS);
}
