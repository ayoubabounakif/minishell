/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:44:46 by khafni            #+#    #+#             */
/*   Updated: 2021/05/05 12:13:07 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINES_H
# define PIPELINES_H
# include "mask.h"
# include "../dlist/dlists.h"
# include "redirection_splitting/reder_split.h"

/*
** A pipeline is a sequence of one or more commands separated by the control operator ‘|’
*/

# define IS_AFTER_PIPE 1
# define IS_AFTER_SEMICOLON 2
# define NO_PIPE_OR_SEMICOLON 3

/*
** after every elementry line we shall know if it's
** followed by a pipe or a semicolon
*/

/*
** the tracked lines will contain the lines + an element that
** states if they're followed by a pipe or ;
*/

typedef struct	s_pipeline *t_pipeline;

struct s_pipeline
{
	char	*cmd_line;
	char	*cmd_line_m;
	char	is_after_p_or_sc;
};

t_pipeline		pipeline(char *cmd_line, char *cmd_line_m, char is_after_p_or_sc);
void			pipeline_destroy(void *pl);

t_arrptr			get_pipelines(char *str);
typedef struct s_tokens *t_tokens;

struct s_tokens
{
	t_dlist tokens;
	t_dlist tokens_masks;
};

t_tokens		tokens(t_pipeline pl);
void			tokens_destroy(t_tokens tks);
#endif