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