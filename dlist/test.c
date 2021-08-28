#include "dlists.h"
#include <stdlib.h>
#include <string.h>

typedef struct _monster
{
	char *name;
	int power_level;
	char *element;
} monster;

monster	*monster_create(char *name, int power_level, char *element)
{
	monster *m = malloc(sizeof(struct _monster));
	m->name = strcpy(strdup(name), name);
	m->element = strcpy(strdup(element), element);
	m->power_level = power_level;
	return (m);
}

void	monster_destroy(void *data)
{
	monster **M_;
	monster *M;

	M_ = data;
	if (*M_ == NULL)
		return ;
	M = *M_;
	free(M->name);
	free(M->element);
	free(M);
	*M_ = NULL;
}

void	*monster_clone(void *data)
{
	monster *M;
	monster *M_cpy;

	M = data;
	M_cpy = monster_create(M->name, M->power_level, M->element);
	return (M_cpy);
}

void monster_print(void *data)
{
	monster *M = data;
	printf("monster name: %s\nmonster power level: %d\nmonster element: %s\n", M->name, M->power_level, M->element);
}

int is_power_level_above_ten(void *data)
{
	monster *M = data;
	return (M->power_level >= 10);
}

int	main()
{	
	t_funPtrs fptrs;
	fptrs.clone = monster_clone;
	fptrs.destroy = monster_destroy;
	fptrs.print = monster_print;
	fptrs.predicate = NULL;
	t_dlist alist = dlist_empty_create(fptrs);
	monster *m1 = monster_create("boogyman", 4, "booger");	
	monster *m2 = monster_create("firemonster", 31, "fire");	
	monster *m3 = monster_create("bruh", 420, "weed");	
	monster *m4 = monster_create("hentaiman", 69, "penis");	
	monster *m5 = monster_create("bogawoga", -4, "goga");	
	dlist_insert_after_cursor(alist, m1);	
	dlist_insert_after_cursor(alist, m2);	
	dlist_insert_after_cursor(alist, m3);	
	dlist_insert_after_cursor(alist, m4);	
	dlist_insert_after_cursor(alist, m5);	
	dlist_print(alist, "; ");
	printf("\n\n");
	t_dlist new_list = dlist_filter_using_clone(alist, is_power_level_above_ten);
	dlist_print(new_list,  " ; ");	
	//monster_destroy(&m1);
	 dlist_destroy_using_destructor(&alist);
	//dlist_destroy_using_destructor(&alist);
	// dlist_destroy_using_destructor(&new_list);
	
	return (0);
}