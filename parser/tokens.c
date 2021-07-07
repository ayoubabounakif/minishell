#include "parser.h"

/*
** tokens take a pipeline aka a cmd_line
** and its mask and returns them as tokens so
** a further parsing on the tokens can be done
** and we can get a command table from every group
** of tokens
*/
t_tokens		tokens(t_pipeline pl)
{
	t_tokens	tk;
	t_rstr		tmp_str;
	t_rstr		tmp_str_m;
	int i;

	tk = malloc(sizeof(struct s_tokens));
	i = 0;
	tmp_str = rstr_create(0);
	tmp_str_m = rstr_create(0);	
	tk->tokens = dlist_empty_create(free, NULL, NULL);
	tk->tokens_masks = dlist_empty_create(free, NULL, NULL);
	while(pl->cmd_line_m[i])
	{
		if (pl->cmd_line_m[i] != 'W')
		{
			rstr_add(tmp_str, pl->cmd_line[i]);
			rstr_add(tmp_str_m, pl->cmd_line_m[i]);
		}
		else if (pl->cmd_line_m[i] == 'W' && tmp_str_m->len > 0)
		{
			dlist_pushback(tk->tokens, rstr_to_cstr(tmp_str));
			dlist_pushback(tk->tokens_masks, rstr_to_cstr(tmp_str_m));
			rstr_clear(tmp_str);
			rstr_clear(tmp_str_m);
		}
		i++;
	}
	if (tmp_str_m->len)
	{
		dlist_pushback(tk->tokens, rstr_to_cstr(tmp_str));
		dlist_pushback(tk->tokens_masks, rstr_to_cstr(tmp_str_m));	
	}
	tokens_split_w_red(tk->tokens);
	tokens_split_w_red(tk->tokens_masks);
	rstr_destroy(tmp_str);
	rstr_destroy(tmp_str_m);
	return (tk);
}

void			tokens_destroy(t_tokens tks)
{
	dlist_destroy(tks->tokens);
	dlist_destroy(tks->tokens_masks);	
	free(tks);
}