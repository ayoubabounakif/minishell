/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:48:35 by khafni            #+#    #+#             */
/*   Updated: 2021/05/26 19:14:08 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"

void    find_env_vars_in_a_token(char *token, char *token_mask)
{
    t_rstr rs;

    rs = rstr_create(0);
    
}

void    print_the_env_variables(t_tokens tks)
{
    dlist_move_cursor_to_head(tks->tokens);
    dlist_move_cursor_to_head(tks->tokens_masks);
    while (tks->tokens->cursor_n != tks->tokens->sentinel)
    {
        if (ft_strnstr((char*)tks->tokens_masks->cursor_n->value, "$", ft_strlen((char*)tks->tokens_masks->cursor_n->value)))
            printf("\n|%s|\n", tks->tokens_masks->cursor_n->value);
        dlist_move_cursor_to_next(tks->tokens);
        dlist_move_cursor_to_next(tks->tokens_masks);
    }
}