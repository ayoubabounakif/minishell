#include "parser.h" 

char *remove_skip_from_skipped_quotes_front(char *a_token)
{
    t_rstr rs;
    t_rstr rs_tmp;
    char    *str;
    int     i;

    rs = cstr_to_rstr(a_token);
    rs_tmp = rstr_create(rs->len - 1);
    i = 1;
    while (i < rs->len)
    {
        rstr_add(rs_tmp, rstr_get(rs, i));
        i++;
    }
    str = rstr_to_cstr(rs_tmp);
    rstr_destroy(rs);
    free(a_token);
    return (str);
}

char *remove_skip_from_skipped_quotes_back(char *a_token)
{
    t_rstr rs;
    t_rstr rs_tmp;
    char    *str;
    int     i;

    rs = cstr_to_rstr(a_token);
    rs_tmp = rstr_create(rs->len - 1);
    i = 0;
    while (i < rs->len - 1)
    {
        rstr_add(rs_tmp, rstr_get(rs, i));
        i++;
    }
    if (a_token[ft_strlen(a_token) - 1] == '\'')
        rstr_set(rs_tmp, i, '\'');
    else if (a_token[ft_strlen(a_token) - 1] == '\"')
        rstr_set(rs_tmp, rs_tmp->len - 1, '\"');
    str = rstr_to_cstr(rs_tmp);
    rstr_destroy(rs);
    free(a_token);
    return (str);
}

char *remove_quotes_from_string(char *a_token)
{
    t_rstr rs;
    t_rstr rs_tmp;
    char    *str;
    int     i;

    rs = cstr_to_rstr(a_token);
    rs_tmp = rstr_create(rs->len - 2);
    i = 1;
    while (i < rs->len - 1)
    {
        rstr_add(rs_tmp, rstr_get(rs, i));
        i++;
    }
    str = rstr_to_cstr(rs_tmp);
    rstr_destroy(rs);
    free(a_token);
    return (str);
}

void process_tokens_from_quotes(t_tokens tks)
{
    char *v;
    char *v_m;
    

    dlist_move_cursor_to_head(tks->tokens);
    dlist_move_cursor_to_head(tks->tokens_masks);
    while (tks->tokens->cursor_n != tks->tokens->sentinel)
    {
        v = tks->tokens->cursor_n->value;
        v_m = tks->tokens_masks->cursor_n->value;
        if (v && (v[0] == '\'' || v[0] == '\"'))
        {
            v = remove_quotes_from_string(v);
            v_m = remove_quotes_from_string(v_m);
            tks->tokens->cursor_n->value = v;
            tks->tokens_masks->cursor_n->value = v_m;
        }
        else if (v && (v[0] == '\\') && ((v[1] == '\'' || v[1] == '\"')))
        {
            v = remove_skip_from_skipped_quotes_front(v);
            v_m = remove_skip_from_skipped_quotes_front(v_m);
            tks->tokens->cursor_n->value = v;
            tks->tokens_masks->cursor_n->value = v_m;
        }
        if (ft_strlen(v) > 3 && (v[ft_strlen(v) - 2] == '\\') && ((v[ft_strlen(v) - 1] == '\'' || v[ft_strlen(v) - 1] == '\"')))
        {
            v = remove_skip_from_skipped_quotes_back(v);
            v_m = remove_skip_from_skipped_quotes_back(v_m);
            tks->tokens->cursor_n->value = v;
            tks->tokens_masks->cursor_n->value = v_m;
        }
        dlist_move_cursor_to_next(tks->tokens);
        dlist_move_cursor_to_next(tks->tokens_masks);
    }
}