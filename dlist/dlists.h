/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlists.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:23:10 by khafni            #+#    #+#             */
/*   Updated: 2021/06/29 19:16:41 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLISTS_H
# define DLISTS_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
** circular doubly linked list module
*/

/*
** function pointer to abstract the node's content distructor
** if are an allocated object at the heap
*/

typedef void	(*t_funDestroy)(void *obj);

/*
** function pointer to abstract the  node's content print
** to console function to 
*/

typedef void	(*t_funPrint)(void *obj);

typedef int		(*t_funCompare)(void *obj1, void *obj2);

typedef int		(*t_Predicate)(void *data);

typedef void*	(*t_funClone)(void *data);

typedef struct s_funPtrs
{
	t_funPrint		print;
	t_funDestroy	destroy;
	t_Predicate		predicate;
	t_funClone		clone;
}	t_funPtrs;

typedef struct s_dlist_cell
{
	void			*value;
	struct s_dlist_cell	*p;
	struct s_dlist_cell	*n;
} t_dlist_cell;

typedef	struct s_dlist_cursor
{
	t_dlist_cell *p;	
	t_dlist_cell *n;	
} t_dlist_cursor;


/*
** the sentinal is the node of the linked list that points to the first
** element of the list and points also to the last element
** and when a list is empty it contains only the sentinal node that points
** to itself 
*/

/*
**	a cursor is just two pointers previous and next that points to
** a position in our linked list such as when we are between two
** nodes previous and next each points to a node and when
** we are at the head of the list the cursor points to the sentinel node
** and the element after it
*/

typedef struct s_dlist
{
	t_dlist_cell	*sentinel;
	t_dlist_cell	*cursorP;
	t_dlist_cell	*cursorN;
	t_funPtrs		funPtrs;
	size_t			len;
}	*t_dlist;

/*
** dlist constructor
*/

/* t_dlist			dlist_empty_create(t_destroy destroy,
					t_compare compare, t_printer printer);
 */

t_dlist			dlist_empty_create(t_funPtrs funPtrs);
/*
**	dlist distructor
*/
void			dlist_destroy(t_dlist *L);

void			dlist_destroy_using_destructor(t_dlist *L_);

/*
** dlist element's insertion methods
*/
void			dlist_insert_after_cursor(t_dlist l, void *value);
void			dlist_insert_before_cursor(t_dlist l, void *value);

/*
** insert element after cursor and move the cursor forward
*/
void			dlist_insert_after_cursor_and_jump(t_dlist l, void *value);
/*
** insert element before cursor and move the cursor backward 
*/
void			dlist_insert_before_cursor_and_jump(t_dlist l, void *value);

/*
**	delete is a boolean set as 0 to not remove
** the content of the element after cursor or set to 1 to remove it
*/

void			dlist_remove_after_cursor(t_dlist l, char delete);
void			dlist_remove_before_cursor(t_dlist l, char delete);
/*
** print list's nodes' content no matter their data type as long
** as the content printing method if provider to the list 
*/
void			dlist_print(t_dlist l, char *sep);
/*
** cursor mouvement methods
*/
void			dlist_move_cursor_to_head(t_dlist l);
void			dlist_move_cursor_to_tail(t_dlist l);
void			dlist_move_cursor_to_next(t_dlist l);
void			dlist_move_cursor_to_previous(t_dlist l);
/*
** dlist setters
*/
void			dlist_set_after_cursor(t_dlist l, void *value, char delete);
void			dlist_set_before_cursor(t_dlist l, void *value, char delete);
/*
**	dlist getters
*/
void			*dlist_get_after_cursor(t_dlist l);
void			*dlist_get_before_cursor(t_dlist l);
/*
**	not needed if the len member of a dlist is used but i like syntatical sugar
*/
char			is_empty_dlist(t_dlist l);
int				dlist_length(t_dlist L);
char			is_dlist_empty(t_dlist L);
char			at_dlist_head(t_dlist L);
char			at_dlist_tail(t_dlist L);

t_dlist_cursor	dlist_get_cursor(t_dlist L);
void			dlist_set_cursor(t_dlist L, t_dlist_cursor C);
void			dlist_map (t_dlist L, void (*f) (void *data));
t_dlist			dlist_maplist (t_dlist L, void *(*f) (void *data), t_funPtrs funPtrs);
t_dlist			dlist_filter(t_dlist L, t_Predicate P);
t_dlist			dlist_filter_using_clone(t_dlist L, t_Predicate P);
#endif