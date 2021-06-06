/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:17:36 by khafni            #+#    #+#             */
/*   Updated: 2021/06/05 17:02:40 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlists.h"

void			dlist_print(t_dlist l, char *sep)
{
	t_dlist_cell	c;
	void			*value;

	if (l->printer == NULL)
		return ;
	printf("L: ("); 
	c = l->sentinel->n;
	while (c != l->sentinel)
	{
		value = c->value;
		(*(l->printer)) (value);
		c = c->n;
		if (c != l->sentinel)
			printf("%s", sep);	
	} 
	printf(")");
}

t_dlist			dlist_empty_create(t_destroy destroy_f, t_compare compare_f, t_printer print_f)
{
	t_dlist	l;

	l = malloc(sizeof(struct s_dlist));
	l->sentinel = malloc(sizeof(struct s_dlist_cell));
	l->sentinel->n = l->sentinel;
	l->sentinel->p = l->sentinel;
	l->cursor_n = l->sentinel;
	l->cursor_p = l->sentinel; 
	l->destroy = destroy_f;
	l->compare = compare_f;
	l->printer = print_f;
	l->len = 0;
	return (l);
}

void			dlist_destroy(void *l_)
{
	t_dlist			l;
	t_dlist_cell	c;
	t_dlist_cell	next;
	
	l = l_;
	c = l->sentinel->n;
	while (c != l->sentinel)
	{
		next = c->n;
		if (l->destroy != NULL)
			(*(l->destroy)) (c->value);
		free(c);
		c = next;	
	}
	free(l->sentinel);
	free(l);
}
