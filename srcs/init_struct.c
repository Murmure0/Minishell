#include "../includes/minishell.h"

void    init_struct(t_shell *shell, char **env)
{
    shell->env = get_env(env);
    shell->path = get_env_paths(env);
}