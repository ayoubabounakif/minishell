#include "../includes/minishell.h"

void    expand_env_variables_test(t_command *cmd, t_dlist env_list)
{
    int i;
    char *mask;

    i = 0;
    while (cmd->tokens[i])
    {
        if (ft_strnstr(cmd->tokens[i], "$", ft_strlen(cmd->tokens[i])))
        {
            mask = get_mask(cmd->tokens[i]);
            cmd->tokens[i] = find_replace_env_vars_in_a_token(cmd->tokens[i], mask, env_list);
        }
        i++;
    }
}
