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

#include "parser.h"
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

char    *find_replace_env_vars_in_a_token(char *token, t_dlist env_list)
{
    t_rstr rs;
    int i;
    char *tmp;
    char *r_str;
    char *is_key_found;
    char *token_mask;

    i = 0;
    tmp = NULL;
    r_str = NULL;
    token_mask = get_mask(token); 
    while(token[i])
    {
        if (token_mask[i] == '$')
        {
            tmp = print_the_env_var(token, token_mask, i);
            is_key_found = find_envv_akey_value(tmp, env_list);
            if(is_key_found)
            {
                if (!r_str)
                    r_str = str_find_and_replace(token, tmp, is_key_found);
                else
                    r_str = str_find_and_replace(r_str, tmp, is_key_found);
            }
            else
            {
                if (!r_str)
                    r_str = str_find_and_replace(token, tmp, "");
                else
                    r_str = str_find_and_replace(r_str, tmp, "");
            }
            free(tmp);
        }
        i++;
    }
    free(token_mask);
    return (r_str);
}

void    expand_env_variables(t_tokens tks, t_dlist env_list)
{
    dlist_move_cursor_to_head(tks->tokens);
    dlist_move_cursor_to_head(tks->tokens_masks);
    while (tks->tokens->cursor_n != tks->tokens->sentinel)
    {
        if (ft_strnstr((char*)tks->tokens_masks->cursor_n->value, "$", ft_strlen((char*)tks->tokens_masks->cursor_n->value)))
        {
            tks->tokens->cursor_n->value = find_replace_env_vars_in_a_token(tks->tokens->cursor_n->value,
            env_list);
            tks->tokens_masks->cursor_n->value = get_mask(tks->tokens->cursor_n->value);
            //printf("\n|%s|\n", tks->tokens->cursor_n->value);
        } 
        dlist_move_cursor_to_next(tks->tokens);
        dlist_move_cursor_to_next(tks->tokens_masks);
    }
}

