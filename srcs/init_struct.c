#include "../includes/minishell.h"

void    init_struct(t_shell *g_shell, char **env)
{
    g_shell->env = get_env(env);
    g_shell->path = get_env_paths(env);
}