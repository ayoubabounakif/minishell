/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:26:19 by khafni            #+#    #+#             */
/*   Updated: 2021/09/14 18:26:22 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_pipeline	pipeline(char *cmd_line, char *cmd_line_m, char is_after_p_or_sc)
{
	t_pipeline	pl;

	pl = malloc(sizeof(struct s_pipeline));
	pl->cmd_line = cmd_line;
	pl->cmd_line_m = cmd_line_m;
	pl->is_after_p_or_sc = is_after_p_or_sc;
	return (pl);
}

void	pipeline_destroy(void *pl_)
{
	t_pipeline	pl;

	pl = (t_pipeline)pl_;
	free(pl->cmd_line);
	free(pl->cmd_line_m);
	free(pl);
}

void	get_pipelines_helper(t_arrptr arr, t_rstr tmp_str,
			t_rstr tmp_str_m, char *str)
{
	int		i;
	char	*mask;

	i = 0;
	mask = get_mask(str);
	while (mask[i])
	{
		if (mask[i] != '|')
		{
			rstr_add(tmp_str, str[i]);
			rstr_add(tmp_str_m, mask[i]);
		}
		else if (mask[i] == '|')
		{	
			if (mask[i] == '|')
			{
				arrptr_add(arr, pipeline(rstr_to_cstr(tmp_str),
						rstr_to_cstr(tmp_str_m), IS_AFTER_PIPE));
			}
			rstr_clear(tmp_str);
			rstr_clear(tmp_str_m);
		}
		i++;
	}
	free(mask);
}

t_arrptr	get_pipelines(char *str)
{
	int			i;
	t_arrptr	arr;
	char		*mask;
	t_rstr		tmp_str;
	t_rstr		tmp_str_m;

	i = 0;
	tmp_str = rstr_create(0);
	tmp_str_m = rstr_create(0);
	arr = empty_arrptr_create(pipeline_destroy);
	mask = get_mask(str);
	get_pipelines_helper(arr, tmp_str, tmp_str_m, str);
	arrptr_add(arr, pipeline(rstr_to_cstr(tmp_str), rstr_to_cstr(tmp_str_m),
			NO_PIPE_OR_SEMICOLON));
	free(mask);
	rstr_destroy(tmp_str);
	rstr_destroy(tmp_str_m);
	return (arr);
}
