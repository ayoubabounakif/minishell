/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reder_split.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 11:55:38 by khafni            #+#    #+#             */
/*   Updated: 2021/04/26 13:14:27 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDER_SPLIT_H
# define REDER_SPLIT_H
//# include "../pipelines.h"
# include "../../dlist/dlists.h"
# include "../../CPCA/generic_parrays/garrptr.h"
# include "../../libft/libft.h"

/*
** here i just try to split tokens that comes in this format
** word + redir sign, redir sign + word or word
** or any words redir signs combination for parsing
** purposes
*/


/*
** is a token composed of a words and rederection signs
*/
int				is_red_cmd_non_split(char *token_);

/*
**	divide a string that contains a 
**	cmd and redirections/appnds or redirections/appnds
**	with the files names into tokens
*/
t_arrptr		split_token_w_red(char *token);

/*
** remplace an individual node in the tokens linked list with
** an array of tokens
*/
void remplace_cursor_node_with_array(t_dlist l, t_arrptr arr);

/*
** takes the splitted tokens and split them again with respect
** to rederection
*/
void			tokens_split_w_red(t_dlist tokens);



#endif