/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:18:54 by khafni            #+#    #+#             */
/*   Updated: 2021/09/07 07:34:26 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "../parser/parser.h"
# include "../dlist/dlists.h"
# include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

unsigned int generate_random_value(void);

int     heredoc_for_one_cmd_table(t_commands_table cmd);

/* typedef s_heredoc
{
    
}	t_heredoc; */
#endif 