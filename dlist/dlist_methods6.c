#include "dlists.h"

t_dlist			dlist_maplist (t_dlist L, void *(*f) (void *data), t_funPtrs funPtrs)
{
	t_dlist			LL;
	t_dlist_cell	*C;
	void			*value;

	LL = dlist_empty_create(funPtrs);
	C = L->sentinel->n;
	while (C != L->sentinel)
	{
		value = (*f)(C->value);
		dlist_insert_after_cursor_and_jump(LL, value);
		C = C->n;
	}
	return (LL);
}

t_dlist			dlist_filter(t_dlist L, t_Predicate P)
{
	t_dlist			LL;
	t_dlist_cell	*C;

	LL = dlist_empty_create(L->funPtrs);
	C = L->sentinel->n;
	while (C != L->sentinel)
	{
		if ((*P)(C->value))
			dlist_insert_after_cursor_and_jump(LL, C->value); 
		C = C->n;
	}
	return (LL);
}

t_dlist			dlist_filter_using_clone(t_dlist L, t_Predicate P)
{
	t_dlist			LL;
	t_dlist_cell	*C;

	LL = dlist_empty_create(L->funPtrs);
	C = L->sentinel->n;
	while (C != L->sentinel)
	{
		if ((*P)(C->value))
			dlist_insert_after_cursor_and_jump(LL, (*(L->funPtrs.clone))(C->value)); 
		C = C->n;
	}
	return (LL);
}

t_funPtrs fun_ptrs(t_funPrint print, t_funDestroy destroy,
	t_funClone clone, t_Predicate predicate)
	{
		t_funPtrs funptrs;

		funptrs.destroy = destroy;
		funptrs.print = print;
		funptrs.clone = clone;
		funptrs.predicate = predicate;
		return (funptrs);
	}