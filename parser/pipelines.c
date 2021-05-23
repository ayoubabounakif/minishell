/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:03:20 by khafni            #+#    #+#             */
/*   Updated: 2021/04/03 15:05:563 15:05:59 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipelines.h"

t_pipeline	pipeline(char *cmd_line, char *cmd_line_m, char is_after_p_or_sc)
{
	t_pipeline pl;

	pl = malloc(sizeof(struct s_pipeline));
	pl->cmd_line = cmd_line;
	pl->cmd_line_m = cmd_line_m;
	pl->is_after_p_or_sc = is_after_p_or_sc;
	return (pl);
}

void			pipeline_destroy(void *pl_)
{
	t_pipeline	pl;

	pl = (t_pipeline)pl_;
	free(pl->cmd_line);
	free(pl->cmd_line_m);
	free(pl);
}

t_arrptr		get_pipelines(char *str)
{
	int 		i;
	t_arrptr	arr;
	char		*mask;
	t_rstr		tmp_str;
	t_rstr		tmp_str_m;

	i = 0;
	tmp_str = rstr_create(0);
	tmp_str_m = rstr_create(0);
	arr = empty_arrptr_create(pipeline_destroy);
	mask = get_mask(str);
	while (mask[i])
	{
		if (mask[i] != ';' && mask[i] != '|')
		{
			rstr_add(tmp_str, str[i]);
			rstr_add(tmp_str_m, mask[i]);
		}
		else if (mask[i] == ';' || mask[i] == '|')
		{
			if (mask[i] == ';')
				arrptr_add(arr, pipeline(rstr_to_cstr(tmp_str), rstr_to_cstr(tmp_str_m),
					IS_AFTER_SEMICOLON));
			else if (mask[i] == '|')
				arrptr_add(arr, pipeline(rstr_to_cstr(tmp_str), rstr_to_cstr(tmp_str_m),
					IS_AFTER_PIPE));
			rstr_clear(tmp_str);
			rstr_clear(tmp_str_m);
		}
		i++;
	}
	arrptr_add(arr, pipeline(rstr_to_cstr(tmp_str), rstr_to_cstr(tmp_str_m),
		NO_PIPE_OR_SEMICOLON));
	free(mask);
	rstr_destroy(tmp_str);
	rstr_destroy(tmp_str_m);
	return (arr);
}

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