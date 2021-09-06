/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:18:54 by khafni            #+#    #+#             */
/*   Updated: 2021/09/06 16:10:36 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "../includes/minishell.h"
# include "../dlist/dlists.h"
# include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

unsigned int generate_random_value(void);

int     heredoc_for_one_cmd_table(t_commands_table cmd);

/* typedef s_heredoc
{
    
}	t_heredoc; */
#endif