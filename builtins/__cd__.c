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

int __cd__(t_commands_table command, t_dlist env_list)
{
	char	*cmd;
	char	*arg;
    
	cmd = command->tokens_simpl[0];
    arg = command->tokens_simpl[1];
    if (arg == NULL) {
        arg = ft_getenv("HOME", env_list);
        if (!arg)
        {
            printErrorMessage(cmd, "HOME not set");
			g_vars.exit_code = 1;
            return (errno);
        }
    }
	if (chdir(arg) == 0)
		return (EXIT_SUCCESS);
	else
	{
		printErrorMessage(cmd, arg);
		g_vars.exit_code = 1;
		return (errno);
	}
	g_vars.exit_code = 0;
	return (EXIT_SUCCESS);
}
