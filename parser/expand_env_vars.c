#include "parser.h"

void    expand_env_variables_test(t_commands_table cmd, t_dlist env_list)
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
}
