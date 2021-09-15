/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstTokenExpander2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:31:44 by khafni            #+#    #+#             */
/*   Updated: 2021/09/15 11:19:58 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_arrptr	first_token_changer(t_arrptr arr)
{
	t_ftc		ftc;

	ftc.arr = arr;
	ftc.arr_r = empty_arrptr_create(free);
	ftc.i = 0;
	ftc.rs = rstr_create(0);
	ftc.str = arrptr_get(ftc.arr, 0);
	ftc.mask = get_mask(ftc.str);
	while (ftc.mask[ftc.i])
	{
		if (ftc.mask[ftc.i] != 'W')
			rstr_add(ftc.rs, ftc.str[ftc.i]);
		else if (ftc.mask[ftc.i] == 'W' && ftc.rs->len)
		{
			arrptr_add(ftc.arr_r, rstr_to_cstr(ftc.rs));
			rstr_clear(ftc.rs);
		}
		ftc.i++;
	}
	if (ftc.rs->len)
		arrptr_add(ftc.arr_r, rstr_to_cstr(ftc.rs));
	rstr_destroy(ftc.rs);
	free(ftc.mask);
	return (ftc.arr_r);
}
