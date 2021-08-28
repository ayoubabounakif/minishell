#include "dlists.h"

char	at_dlist_head(t_dlist L)
{
	return (L->cursorP == L->sentinel);
}

char	at_dlist_tail(t_dlist L)
{
	return (L->cursorN == L->sentinel);
}

t_dlist_cursor	dlist_get_cursor(t_dlist L)
{
	t_dlist_cursor	C;

	C.p = L->cursorP;
	C.n = L->cursorN;
	return (C);
}

void	dlist_set_cursor(t_dlist L, t_dlist_cursor C)
{
	L->cursorN = C.n;
	L->cursorP = C.p;
}

 void			dlist_map (t_dlist L, void (*f) (void *data))
 {
	t_dlist_cell *C;
	 
	C = L->sentinel->n;
	while (C != L->sentinel)
	{
		(*f)(C->value);
		C = C->n;
	}
 }
