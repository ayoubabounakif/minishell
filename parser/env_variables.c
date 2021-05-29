/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:48:35 by khafni            #+#    #+#             */
/*   Updated: 2021/05/29 15:54:14y khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"
/* t_arrptr rstr_find_needle(t_rstr rs, char *needle)
{
    t_arrptr arr;

    arr = empty_arrptr_create(NULL);
    arrptr_add()
    
} */


char *rstr_find_and_replace(t_rstr haystack, char *needle, char *new_needle)
{
    int i;
    int j;
    t_rstr rs;
    char *str;
    
    i = 0;
    rs = rstr_create(0); 
    while (i < haystack->len)
    {
        j = 0;
        while (needle[j] && (needle[j] == rstr_get(haystack, i + j))
        && (i + j) < haystack->len)
            j++;
        if (j == (ft_strlen(needle)))
        {
            i += j;
            j = 0;
            while (new_needle[j])
                rstr_add(rs, new_needle[j++]);
        }
        else
        {
            rstr_add(rs, rstr_get(haystack, i));
            i++;
        }
    }
    str = rstr_to_cstr(rs);
    rstr_destroy(rs);
    return (str);
}


char *str_find_and_replace(char *haystack, char *needle, char *new_needle)
{
    t_rstr haystack_;
    char *rslt;

    haystack_ = cstr_to_rstr(haystack);
    rslt = rstr_find_and_replace(haystack_, needle, new_needle);
    //rstr_destroy(haystack_);
    return(rslt);
}

/* char    *remplace_env_var(char *token, int s_envpos, int e_envpos)
{
    t_rstr rs;
    int i;

    i = 0;
    rs = rstr_create(0);
    while (token[i] && i < s_envpos)
    {
        rstr_add(rs, token[i]);
        i++;
    }
    i = 0;
    while("potato"[i])
    {
        rstr_add(rs, "potato"[i]);
        i++;
    }
    i = e_envpos;
    while(e_envpos < ft_strlen(token) && token[i])
    {
        rstr_add(rs, token[i]);
        i++;
    }
    return (rstr_to_cstr(rs));
} */

char *print_the_env_var(char *token, char *token_mask, int i)
{
    t_rstr rs;
    int s_envpos;
    char *r_str;

    rs = rstr_create(0);
    rstr_add(rs, '$');
    s_envpos = i;
    i++;
    while (token_mask[i] && token_mask[i] == 'V')
    {
        rstr_add(rs, token[i]);
        i++;
    }
      
    r_str = rstr_to_cstr(rs);
    rstr_destroy(rs);
    return (r_str);
    
}

char    *find_env_vars_in_a_token(char *token, char *token_mask)
{
    t_rstr rs;
    int i;
    char *tmp;
    char *r_str;

    i = 0;
    tmp = NULL;
    r_str = NULL;
    while(token[i])
    {
        if (token_mask[i] == '$')
        {
            tmp = print_the_env_var(token, token_mask, i);
            if (!r_str)
                r_str = str_find_and_replace(token, tmp, "|O_O|");
            else
                r_str = str_find_and_replace(r_str, tmp, "|#_#|");
            free(tmp);
        }
        i++;
    }
    return (r_str);
}

void    expand_env_variables(t_tokens tks)
{
    dlist_move_cursor_to_head(tks->tokens);
    dlist_move_cursor_to_head(tks->tokens_masks);
    while (tks->tokens->cursor_n != tks->tokens->sentinel)
    {
        if (ft_strnstr((char*)tks->tokens_masks->cursor_n->value, "$", ft_strlen((char*)tks->tokens_masks->cursor_n->value)))
        {
            tks->tokens->cursor_n->value = find_env_vars_in_a_token(tks->tokens->cursor_n->value,
            tks->tokens_masks->cursor_n->value);
            tks->tokens_masks->cursor_n->value = get_mask(tks->tokens->cursor_n->value);
            //printf("\n|%s|\n", tks->tokens->cursor_n->value);
        }
        printf("\n|%s|\n", tks->tokens_masks->cursor_n->value);
        dlist_move_cursor_to_next(tks->tokens);
        dlist_move_cursor_to_next(tks->tokens_masks);
    }
}