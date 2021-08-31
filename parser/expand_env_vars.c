#include "parser.h"

/* void    expand_env_variables_test(t_commands_table cmd, t_dlist env_list)
{
    int i;
    char *mask;

    i = 0;
    while (cmd->tokens_simpl[i])
    {
        if (ft_strnstr(cmd->tokens_simpl[i], "$", ft_strlen(cmd->tokens_simpl[i])))
        {
            mask = get_mask(cmd->tokens_simpl[i]);
            cmd->tokens_simpl[i] = find_replace_env_vars_in_a_token(cmd->tokens_simpl[i], mask, env_list);
        }
        i++;
    }
} */

void		expandEnvVarsInParsedData(t_dlist parsed_data_lst, t_dlist env_lst)
{
    char    **token_array;
    int     i;

    i = 0;
    dlist_move_cursor_to_head(parsed_data_lst);
    while (parsed_data_lst->cursor_n != parsed_data_lst->sentinel)
    {
        token_array = ((t_commands_table)parsed_data_lst->cursor_n->value)->tokens_simpl;
        while ((i < ((t_commands_table)parsed_data_lst->cursor_n->value)->tokens->len))
        {
            
           /*  if (ft_strnstr(token_array[i], "$?", ft_strlen(token_array[i])))
                token_array[i] = str_find_and_replace(token_array[i], "$?", ); */

            if (ft_strnstr(token_array[i], "$", ft_strlen(token_array[i])))
                token_array[i] = find_replace_env_vars_in_a_token(token_array[i], env_lst); 
            i++;
        }
        dlist_move_cursor_to_next(parsed_data_lst);
    }
}