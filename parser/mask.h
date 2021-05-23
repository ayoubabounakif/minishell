/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:54:43 by khafni            #+#    #+#             */
/*   Updated: 2021/04/02 16:36:40 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MASK_H
# define MASK_H

# include "../libft/libft.h"
# include "../CPCA/generic_parrays/garrptr.h"

# define IS_AFTER_PIPE 1
# define IS_AFTER_SEMICOLON 2
# define NO_PIPE_OR_SEMICOLON 3

/*
					The way to parse below:

	echo "hello world these characters can't be escaped in double quotes: this one \\ and this one \$ and this one \", example: $PWD" 'literal' \$PWD | grep \P"W"'D';>>2 echo 123 > 1;>1 echo notempty;<1 cat;echo " $PWD " $PWD ' $PWD ' \$PWD "$"PWD '$'PWD
	NNNNW"SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS\LSSSSSSSSSSSSSS\LSSSSSSSSSSSSSS\LSSSSSSSSSSS$VVV"W'LLLLLLL'W\LNNNW|WNNNNW\L"S"'L';22NWNNNNWNNNW>WN;>NWNNNNWNNNNNNNN;<NWNNN;NNNNW"S$VVVS"W$VVVW'LLLLLL'W\LNNNW"S"NNNW'L'NNN
	N = non-literal
	S = semi-literal
	L = literal
	V = env-variable
	22 = redir-append = >>
	> = redir-trunc, itself
	< = redir-in, itself
	; = itself
	| = itself
	' = itself
	" = itself
	\ = itself

*/

/*
** state represents where we're exactly on the command
*/
typedef struct	s_state
{
	char	skip;
	char	inside_squote;
	char	inside_dquote;
	char	inside_dquotes_sk;	
	char	env_variable;
	char	env_variable_dq;
}				t_state;

void		init_states(t_state *state);
char		get_mask_char_inside_dq(t_state *state, char *s, int i);
char		get_mask_character(t_state *state, char *s, int i);
char	    *get_mask(char *s);
t_arrptr	split_using_mask(char *str, char *str_mask, char del);


#endif