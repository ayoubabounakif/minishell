/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlists.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:23:10 by khafni            #+#    #+#             */
/*   Updated: 2021/05/28 11:19:36 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
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

typedef void	(*t_destroy)(void *obj);

/*
** function pointer to abstract the  node's content print
** to console function to 
*/

typedef void	(*t_printer)(void *obj);

/*
** function pointer to abstract
*/

typedef int		(*t_compare)(void *obj1, void *obj2);


typedef struct s_dlist_cell *t_dlist_cell;

struct	s_dlist_cell
{
	void			*value;
	t_dlist_cell	p;	
	t_dlist_cell	n;
};

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

typedef struct s_dlist	*t_dlist;

struct s_dlist
{
	t_dlist_cell	sentinel;
	t_dlist_cell	cursor_p;
	t_dlist_cell	cursor_n;
	t_destroy		destroy;
	t_printer		printer;
	t_compare		compare;
	size_t			len;
};

/*
** dlist constructor
*/

t_dlist			dlist_empty_create(t_destroy destroy, t_compare compare, t_printer printer);
/*
**	dlist distructor
*/
void			dlist_destroy(void *l_);

/*
** dlist element's insertion methods
*/
void			dlist_insert_after_cursor(t_dlist l, void *value);
void			dlist_insert_before_cursor(t_dlist l, void *value);

/*
** insert element after cursor and move the cursor forward
*/
void			dlist_insert_after_cursor_n_move_n(t_dlist l, void *value);
/*
** insert element before cursor and move the cursor backward 
*/
void			dlist_insert_before_cursor_n_move_p(t_dlist l, void *value);

/*
**	delete is a boolean set as 0 to not remove the content of the element after cursor
**	or set to 1 to remove it
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
void			*dlist_get_after_cursor(t_dlist l, char delete);
void			*dlist_get_before_cursor(t_dlist l, char delete);
/*
**	not needed if the len member of a dlist is used but i like syntatical sugar
*/
char			is_empty_dlist(t_dlist l);

/*
**	pushing an element to the end of the list
*/
void			dlist_pushback(t_dlist l, void *value);

#endif